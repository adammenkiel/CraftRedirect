#include "protocol/packet/packets/server_bound/status/status_request_packet.hpp"

status_request_packet::status_request_packet() {}

status_request_packet::~status_request_packet() {}

uint32_t status_request_packet::get_packet_id() {
    return 0;
}

packet_state status_request_packet::get_state() {
    return packet_state::STATUS;
}

void status_request_packet::read(input_stream& input) {}

void status_request_packet::write(output_stream& output) {}

std::unique_ptr<packet> status_request_packet::clone() {
    return std::make_unique<status_request_packet>(*this);
}