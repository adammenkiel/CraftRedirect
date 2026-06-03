#include "protocol/packet/packets/server_bound/handshake_packet.hpp"

handshake_packet::handshake_packet(
            uint32_t version_number,
            std::string server_host,
            uint32_t server_port,
            uint8_t state
        ) : 
        version_number(version_number),
        server_host(server_host),
        server_port(server_port),
        state(state) {}

handshake_packet::~handshake_packet() {}

uint32_t handshake_packet::get_packet_id() {
    return 0;
}

void handshake_packet::read(input_stream& input) {
    version_number = input.readVarInt();
    server_host = input.readString();
    server_port = input.readVarInt();
    state = input.readByte();
}

void handshake_packet::write(output_stream& output) {
    output.writeVarInt(version_number);
    output.writeString(server_host);
    output.writeVarInt(server_port);
    output.writeByte(state);
}