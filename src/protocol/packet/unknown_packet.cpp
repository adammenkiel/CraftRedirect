#include "protocol/packet/unknown_packet.hpp"

unknown_packet::unknown_packet(
    packet_state state,
    uint32_t packet_id,
    std::vector<uint8_t> packet_bytes
) :
    state(state),
    packet_id(packet_id),
    packet_bytes(packet_bytes) {}


unknown_packet::unknown_packet(
    packet_state state,
    uint32_t packet_id
) :
    state(state),
    packet_id(packet_id),
    packet_bytes(std::vector<uint8_t>()) {}

unknown_packet::unknown_packet() {}

unknown_packet::~unknown_packet() {}

uint32_t unknown_packet::get_packet_id() {
    return this->packet_id;
}

packet_state unknown_packet::get_state() {
    return this->state;
}

void unknown_packet::read(input_stream& input) {
    packet_bytes = input.readFully();
}

void unknown_packet::write(output_stream& output) {
    output.writeBytes(packet_bytes);
}

std::unique_ptr<packet> unknown_packet::clone() {
    return std::make_unique<unknown_packet>(*this);
}