#include <chrono>

#include "craft_redirect_server.hpp"

#include "protocol/packet/unknown_packet.hpp"

#include "command/commands/test_command.hpp"

#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"
#include "protocol/packet/packets/server_bound/status/status_request_packet.hpp"
#include "protocol/packet/packets/server_bound/status/ping_request_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_acknowledged_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/client_information_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/known_packs_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/finish_configuration_packet.hpp"
#include "protocol/packet/packets/server_bound/play/chat_command_packet.hpp"

#include "protocol/packet/packets/client_bound/play/client_keep_alive_packet.hpp"
#include "protocol/packet/packets/client_bound/configuration/client_known_packs_packet.hpp"
#include "protocol/packet/packets/client_bound/configuration/config_payload_packet.hpp"
#include "protocol/packet/packets/client_bound/configuration/feature_flags_packet.hpp"
#include "protocol/packet/packets/client_bound/status/status_response_packet.hpp"
#include "protocol/packet/packets/client_bound/status/ping_response_packet.hpp"
#include "protocol/packet/packets/client_bound/login/login_success_packet.hpp"
#include "protocol/packet/packets/client_bound/play/system_chat_message_packet.hpp"

void craft_redirect_server::registerAllPackets() {
    spdlog::info("Registering packets...");
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
    chat_command_packet chat_command = chat_command_packet();
    packets.register_packet(packet_bound::SERVER, packet_state::PLAY, chat_command);


    client_keep_alive_packet client_keep_alive = client_keep_alive_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::PLAY, client_keep_alive);
    client_known_packs_packet client_known_packs = client_known_packs_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::CONFIGURATION, client_known_packs);
    config_payload_packet conf_payload = config_payload_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::CONFIGURATION, conf_payload);
    feature_flags_packet feature_flags = feature_flags_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::CONFIGURATION, feature_flags);
    status_response_packet response = status_response_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::STATUS, response);
    ping_response_packet ping_response = ping_response_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::STATUS, ping_response);
    login_success_packet login_success = login_success_packet();
    packets.register_packet(packet_bound::CLIENT, packet_state::LOGIN, login_success);
    //system_chat_message_packet system_chat_message = system_chat_message_packet();
    //packets.register_packet(packet_bound::CLIENT, packet_state::PLAY, system_chat_message);
    spdlog::info("Finished!");
}

void craft_redirect_server::registerCommands() {
    command_map["test"] = std::make_shared<test_command>();
}

void craft_redirect_server::loadRegistryPackets() {

    boost::asio::io_context io;
    spdlog::info("Loading registry_data.bin ...");
    auto decoder = packet_decoder(packets);
    boost::asio::stream_file file(io, "registry_data.bin", boost::asio::stream_file::read_only);
    try {
        while(true) {
             std::unique_ptr<packet> config_packet = decoder.readPacket(packet_bound::CLIENT, packet_state::CONFIGURATION, file);
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
    
    std::shared_ptr<craft_redirect_server> server = shared_from_this();

    std::vector<std::thread> threads;
    spdlog::info("Server started on: 127.0.0.1:12121 !");
    
    //temporary solution
    threads.emplace_back([server]() mutable {
        while(true) {
            client_keep_alive_packet packet = client_keep_alive_packet(0);
            for(std::shared_ptr<session> s : server->sessions) {
                try {
                    if(s->state == packet_state::PLAY)
                        s->sendPacket(packet);
                } catch(std::exception& err) {}
            }
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });
    
    while(true) {
        tcp::socket socket = acceptor.accept();
        threads.emplace_back([socket = std::move(socket), server]() mutable {
            packet_state current_state = packet_state::HANDSHAKE;
            std::shared_ptr<session> player_session = std::make_shared<session>(server, socket);
            auto decoder = packet_decoder(server->packets);
            try {
                while(true) {
                    player_session->handle(std::move(decoder.readPacket(packet_bound::SERVER, player_session->state, socket)));
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
    this->registerCommands();
    this->startServer();
}