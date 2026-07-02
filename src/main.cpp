#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"
#include "protocol/packet/packet_registry.hpp"
#include "protocol/codec/packet_decoder.hpp"

#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"
#include "protocol/packet/packets/server_bound/status/status_request_packet.hpp"
#include "protocol/packet/packets/server_bound/status/ping_request_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_acknowledged_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/client_information_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/known_packs_packet.hpp"

#include "protocol/packet/packets/client_bound/status/status_response_packet.hpp"
#include "protocol/packet/packets/client_bound/status/ping_response_packet.hpp"
#include "protocol/packet/packets/client_bound/login/login_success_packet.hpp"
#include "session/session.hpp"

using boost::asio::ip::tcp;

int main() {

    auto packets = std::make_shared<packet_registry>();

    handshake_packet handshake = handshake_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::HANDSHAKE, handshake);
    login_start_packet login_start = login_start_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::LOGIN, login_start);
    status_request_packet request = status_request_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::STATUS, request);
    ping_request_packet ping_request = ping_request_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::STATUS, ping_request);
    login_acknowledged_packet login_acknowledged = login_acknowledged_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::LOGIN, login_acknowledged);
    client_information_packet client_information = client_information_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::CONFIGURATION, client_information);
    known_packs_packet known_packs = known_packs_packet();
    packets->register_packet(packet_bound::SERVER, packet_state::CONFIGURATION, known_packs);


    status_response_packet response = status_response_packet();
    packets->register_packet(packet_bound::CLIENT, packet_state::STATUS, response);
    ping_response_packet ping_response = ping_response_packet();
    packets->register_packet(packet_bound::CLIENT, packet_state::STATUS, ping_response);
    login_success_packet login_success = login_success_packet();
    packets->register_packet(packet_bound::CLIENT, packet_state::LOGIN, login_success);

    auto decoder = std::make_shared<packet_decoder>(packets);

    boost::asio::io_context io;
    boost::asio::stream_file file(io, "registry_data.bin", boost::asio::stream_file::read_only);

    tcp::endpoint endpoint(tcp::v4(), 12121);
    tcp::acceptor acceptor(io);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    
    std::vector<std::thread> threads;

    while(true) {
        tcp::socket socket = acceptor.accept();
        threads.emplace_back([socket = std::move(socket), decoder]() mutable {
            packet_state current_state = packet_state::HANDSHAKE;
            bool compression = false;
            session player_session(socket);
            try {
                while(true) {
                    std::unique_ptr<packet> packet = decoder->readPacket(packet_bound::SERVER, player_session.state, socket);
                    player_session.handle(std::move(packet));

                }
            } catch(std::exception& err) {
                spdlog::info("Disconnected! Reason: {}", err.what());
                socket.close();
                return;
            }
        });
    }
    //test_connection("localhost", "25565");
    return 0;
}