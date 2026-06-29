#include "protocol/packet/packets/server_bound/login/login_acknowledged_packet.hpp"

login_acknowledged_packet::login_acknowledged_packet() {}

login_acknowledged_packet::~login_acknowledged_packet() {}

uint32_t login_acknowledged_packet::get_packet_id() {
    return 3;
}

packet_state login_acknowledged_packet::get_state() {
    return packet_state::STATUS;
}

void login_acknowledged_packet::read(input_stream& input) {}

void login_acknowledged_packet::write(output_stream& output) {}

std::unique_ptr<packet> login_acknowledged_packet::clone() {
    return std::make_unique<login_acknowledged_packet>(*this);
}