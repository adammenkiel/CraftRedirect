#include "protocol/packet/packets/client_bound/configuration/config_payload_packet.hpp"

config_payload_packet::config_payload_packet(
        std::string tag,
        std::vector<uint8_t> data
) : 
    tag(tag),
    data(data) {}

config_payload_packet::config_payload_packet() {}

config_payload_packet::~config_payload_packet() {}

uint32_t config_payload_packet::get_packet_id() {
    return 1;
}

packet_state config_payload_packet::get_state() {
    return packet_state::CONFIGURATION;
}

void config_payload_packet::read(input_stream& input) {
    tag = input.readString();
    data = input.readFully();
}

void config_payload_packet::write(output_stream& output) {
    output.writeString(tag);
    output.writeBytes(data);
}

std::unique_ptr<packet> config_payload_packet::clone() {
    return std::make_unique<config_payload_packet>(*this);
}