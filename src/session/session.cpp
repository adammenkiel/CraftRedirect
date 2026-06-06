#include <iostream>
#include <spdlog/spdlog.h>

#include "session.hpp"
#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"

session::session(tcp::socket& socket) : socket(socket) {}

void session::handle(std::unique_ptr<packet> handled_packet) {
    if(dynamic_cast<handshake_packet*>(handled_packet.get())) {
        spdlog::info("Received handshake packet!");
        state = packet_state::LOGIN;        
    }
}

void session::sendPacket(packet& packet) {
    output_stream data_stream;
    data_stream.writeVarInt(packet.get_packet_id());
    packet.write(data_stream);
    std::vector<uint8_t> data_buffer = data_stream.get_buffer();
    
    output_stream packet_stream;
    packet_stream.writeVarInt(data_buffer.size());
    packet_stream.writeBytes(data_buffer);
    
    boost::asio::write(
        socket,
        boost::asio::buffer(packet_stream.get_buffer())
    );
}