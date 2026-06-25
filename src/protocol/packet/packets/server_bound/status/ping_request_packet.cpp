#include "protocol/packet/packets/server_bound/status/ping_request_packet.hpp"

ping_request_packet::ping_request_packet(
    std::uint64_t time
) : 
time(time) {}

ping_request_packet::ping_request_packet() {}

ping_request_packet::~ping_request_packet() {}

uint32_t ping_request_packet::get_packet_id() {
    return 1;
}

packet_state ping_request_packet::get_state() {
    return packet_state::STATUS;
}

void ping_request_packet::read(input_stream& input) {
    time = input.readLong();
}

void ping_request_packet::write(output_stream& output) {
    output.writeLong(time);
}

std::unique_ptr<packet> ping_request_packet::clone() {
    return std::make_unique<ping_request_packet>(*this);
}