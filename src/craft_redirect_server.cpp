#include "craft_redirect_server.hpp"

#include "protocol/packet/unknown_packet.hpp"

#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"
#include "protocol/packet/packets/server_bound/status/status_request_packet.hpp"
#include "protocol/packet/packets/server_bound/status/ping_request_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_acknowledged_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/client_information_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/known_packs_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/finish_configuration_packet.hpp"

#include "protocol/packet/packets/client_bound/status/status_response_packet.hpp"
#include "protocol/packet/packets/client_bound/status/ping_response_packet.hpp"
#include "protocol/packet/packets/client_bound/login/login_success_packet.hpp"

void craft_redirect_server::registerAllPackets() {
    handshake_packet handshake = handshake_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::HANDSHAKE, handshake);
    login_start_packet login_start = login_start_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::LOGIN, login_start);
    status_request_packet request = status_request_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::STATUS, request);
    ping_request_packet ping_request = ping_request_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::STATUS, ping_request);
    login_acknowledged_packet login_acknowledged = login_acknowledged_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::LOGIN, login_acknowledged);
    client_information_packet client_information = client_information_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::CONFIGURATION, client_information);
    known_packs_packet known_packs = known_packs_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::CONFIGURATION, known_packs);
    finish_configuration_packet finish_config = finish_configuration_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::CONFIGURATION, finish_config);

    status_response_packet response = status_response_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::STATUS, response);
    ping_response_packet ping_response = ping_response_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::STATUS, ping_response);
    login_success_packet login_success = login_success_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::LOGIN, login_success);
}

void craft_redirect_server::loadRegistryPackets() {

    boost::asio::io_context io;
    spdlog::info("Loading registry_data.bin ...");
    auto decoder = packet_decoder(packets);
    boost::asio::stream_file file(io, "registry_data.bin", boost::asio::stream_file::read_only);
    try {
        while(true) {
             std::unique_ptr<packet> config_packet = decoder.readPacket(packet_bound::CLIENT, packet_state::CONFIGURATION, file);
             spdlog::info("Loaded config packet ID: {0} ", config_packet->get_packet_id());
             if(auto* received_unknown_packet = dynamic_cast<unknown_packet*>(config_packet.get())) {
                spdlog::info("Size len: {0}", received_unknown_packet->packet_bytes.size());
             }
             this->config_packets.push_back(std::move(config_packet));
        }
    } catch(std::exception& err) {
        spdlog::info("Registry and Update Tags packets loaded from registry_data.bin!");
    }
}

void craft_redirect_server::startServer() {
    

    spdlog::info("Server is starting......");
    boost::asio::io_context io;
    tcp::endpoint endpoint(tcp::v4(), 12121);
    tcp::acceptor acceptor(io);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    
    std::vector<std::thread> threads;
    spdlog::info("Server started on: 127.0.0.1:12121 !");
    while(true) {
        tcp::socket socket = acceptor.accept();
        std::shared_ptr<craft_redirect_server> server = shared_from_this();
        threads.emplace_back([socket = std::move(socket), server]() mutable {
            packet_state current_state = packet_state::HANDSHAKE;
            bool compression = false;
            session player_session(server, socket);
            auto decoder = packet_decoder(server->packets);
            try {
                while(true) {
                    std::unique_ptr<packet> packet = decoder.readPacket(packet_bound::SERVER, player_session.state, socket);
                    player_session.handle(std::move(packet));

                }
            } catch(std::exception& err) {
                spdlog::info("Disconnected! Reason: {}", err.what());
                socket.close();
                return;
            }
        });
    }
}

void craft_redirect_server::run() {
    this->registerAllPackets();
    this->loadRegistryPackets();
    this->startServer();
}