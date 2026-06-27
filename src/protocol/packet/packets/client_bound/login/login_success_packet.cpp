#include "protocol/packet/packets/client_bound/login/login_success_packet.hpp"

login_success_packet::login_success_packet(
    std::vector<uint8_t> uuid_bytes,
    std::string username,
    std::vector<login_success_property> properties,
    bool strict_error_handling
) : 
    uuid_bytes(uuid_bytes),
    username(username),
    properties(properties),
    strict_error_handling(strict_error_handling) {}

login_success_packet::login_success_packet() {}

login_success_packet::~login_success_packet() {}

uint32_t login_success_packet::get_packet_id() {
    return 2;
}

packet_state login_success_packet::get_state() {
    return packet_state::STATUS;
}

void login_success_packet::read(input_stream& input) {
    uuid_bytes = input.readBytes(16);
    username = input.readString();
    properties = input.readProperties();
    strict_error_handling = input.readByte() != 0;
}

void login_success_packet::write(output_stream& output) {
    output.writeBytes(uuid_bytes);
    output.writeString(username);
    output.writeProperties(properties);
    output.writeByte(strict_error_handling);
}

std::unique_ptr<packet> login_success_packet::clone() {
    return std::make_unique<login_success_packet>(*this);
}