#include "protocol/packet/packets/client_bound/play/client_keep_alive_packet.hpp"

client_keep_alive_packet::client_keep_alive_packet(
    uint64_t value
) : 
value(value) {}

client_keep_alive_packet::client_keep_alive_packet() {}

client_keep_alive_packet::~client_keep_alive_packet() {}

uint32_t client_keep_alive_packet::get_packet_id() {
    return 0x26;
}

packet_state client_keep_alive_packet::get_state() {
    return packet_state::PLAY;
}

void client_keep_alive_packet::read(input_stream& input) {
    value = input.readLong();
}

void client_keep_alive_packet::write(output_stream& output) {
    output.writeLong(value);
}

std::unique_ptr<packet> client_keep_alive_packet::clone() {
    return std::make_unique<client_keep_alive_packet>(*this);
}