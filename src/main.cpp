#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"
#include "test/test_connection.hpp"
#include "protocol/packet/packet_registry.hpp"
#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"
#include "session/session.hpp"

using boost::asio::ip::tcp;

int main() {

    packet_registry packets;

    handshake_packet handshake = handshake_packet();
    packets.register_packet(
        packet_bound::SERVER,
        packet_state::HANDSHAKE,
        handshake
    );

    login_start_packet login_start = login_start_packet();
    packets.register_packet(
        packet_bound::SERVER,
        packet_state::LOGIN,
        login_start
    );

    boost::asio::io_context io;
    tcp::endpoint endpoint(tcp::v4(), 25565);
    tcp::acceptor acceptor(io);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    
    std::vector<std::thread> threads;

    while(true) {
        tcp::socket socket = acceptor.accept();
        spdlog::info("Socket connecting");
        threads.emplace_back([socket = std::move(socket), packets = std::move(packets)]() mutable {
            packet_state current_state = packet_state::HANDSHAKE;
            bool compression = false;
            session player_session(socket);

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
                std::unique_ptr<packet> packet = packets.get_packet_by_id(packet_bound::SERVER, current_state, packet_id);
                packet->read(input_stream);
                player_session.handle(std::move(packet));

            }
        });
    }
    //test_connection("localhost", "25565");
    return 0;
}