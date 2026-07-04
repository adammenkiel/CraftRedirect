#include "protocol/packet/packets/server_bound/configuration/finish_configuration_packet.hpp"

finish_configuration_packet::finish_configuration_packet() {}

finish_configuration_packet::~finish_configuration_packet() {}

uint32_t finish_configuration_packet::get_packet_id() {
    return 3;
}

packet_state finish_configuration_packet::get_state() {
    return packet_state::CONFIGURATION;
}

void finish_configuration_packet::read(input_stream& input) {}

void finish_configuration_packet::write(output_stream& output) {}

std::unique_ptr<packet> finish_configuration_packet::clone() {
    return std::make_unique<finish_configuration_packet>(*this);
}