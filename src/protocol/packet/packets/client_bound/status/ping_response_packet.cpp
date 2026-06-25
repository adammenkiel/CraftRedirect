#include "protocol/packet/packets/client_bound/status/ping_response_packet.hpp"

ping_response_packet::ping_response_packet(
    std::uint64_t time
) : 
time(time) {}

ping_response_packet::ping_response_packet() {}

ping_response_packet::~ping_response_packet() {}

uint32_t ping_response_packet::get_packet_id() {
    return 1;
}

packet_state ping_response_packet::get_state() {
    return packet_state::STATUS;
}

void ping_response_packet::read(input_stream& input) {
    time = input.readLong();
}

void ping_response_packet::write(output_stream& output) {
    output.writeLong(time);
}

std::unique_ptr<packet> ping_response_packet::clone() {
    return std::make_unique<ping_response_packet>(*this);
}