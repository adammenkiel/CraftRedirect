#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"

login_start_packet::login_start_packet(
    std::string username,
    std::vector<uint8_t> uuid_bytes
) : 
    username(username),
    uuid_bytes(uuid_bytes) {}

login_start_packet::~login_start_packet() {}

uint32_t login_start_packet::get_packet_id() {
    return 0;
}

packet_state login_start_packet::get_state() {
    return packet_state::LOGIN;
}

void login_start_packet::read(input_stream& input) {
    username = input.readString();
    uuid_bytes = input.readBytes(16);
}

void login_start_packet::write(output_stream& output) {
    output.writeString(username);
    output.writeBytes(uuid_bytes);
}

std::unique_ptr<packet> login_start_packet::clone() {
    return std::make_unique<login_start_packet>(*this);
}