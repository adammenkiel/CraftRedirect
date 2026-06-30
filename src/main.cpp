#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"
#include "protocol/packet/packet_registry.hpp"

#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"
#include "protocol/packet/packets/server_bound/status/status_request_packet.hpp"
#include "protocol/packet/packets/server_bound/status/ping_request_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_acknowledged_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/client_information_packet.hpp"

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


    status_response_packet response = status_response_packet();
    packets->register_packet(packet_bound::CLIENT, packet_state::STATUS, response);
    ping_response_packet ping_response = ping_response_packet();
    packets->register_packet(packet_bound::CLIENT, packet_state::STATUS, ping_response);
    login_success_packet login_success = login_success_packet();
    packets->register_packet(packet_bound::CLIENT, packet_state::LOGIN, login_success);


    boost::asio::io_context io;
    tcp::endpoint endpoint(tcp::v4(), 12121);
    tcp::acceptor acceptor(io);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    
    std::vector<std::thread> threads;

    while(true) {
        tcp::socket socket = acceptor.accept();
        threads.emplace_back([socket = std::move(socket), packets]() mutable {
            packet_state current_state = packet_state::HANDSHAKE;
            bool compression = false;
            session player_session(socket);
            try {
                while(true) {
                    uint32_t packetLengthTemp = 0;
                    int position = 0;
                    uint8_t currentByte;

                    while (true) {
                        boost::asio::read(socket, boost::asio::buffer(&currentByte, 1));
                        packetLengthTemp |= (currentByte & 0x7F) << position;
                        if ((currentByte & 0x80) == 0) break;
                        position += 7;
                        if (position >= 32) throw std::runtime_error("VarInt is too big"); // temporary
                    }
                    std::vector<uint8_t> packetBytes(packetLengthTemp);
                    boost::asio::read(socket, boost::asio::buffer(packetBytes));
                    input_stream input_stream(packetBytes);

                    uint32_t packet_id = input_stream.readVarInt(); //temporary
                    std::unique_ptr<packet> packet = packets->get_packet_by_id(packet_bound::SERVER, player_session.state, packet_id);
                    packet->read(input_stream);
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