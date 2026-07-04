#include "protocol/packet/packets/client_bound/configuration/feature_flags_packet.hpp"

feature_flags_packet::feature_flags_packet(
            uint32_t len,
            std::vector<std::string> flags
) : 
    len(len),
    flags(flags) {}

feature_flags_packet::feature_flags_packet() {}

feature_flags_packet::~feature_flags_packet() {}

uint32_t feature_flags_packet::get_packet_id() {
    return 0x0C;
}

packet_state feature_flags_packet::get_state() {
    return packet_state::CONFIGURATION;
}

void feature_flags_packet::read(input_stream& input) {
    len = input.readVarInt();
    for(int i = 0; i < len; i++) {
        flags.push_back(input.readString());
    }
}

void feature_flags_packet::write(output_stream& output) {
    output.writeVarInt(len);
    for(int i = 0; i < len; i++) {
        output.writeString(flags[i]);
    }
}

std::unique_ptr<packet> feature_flags_packet::clone() {
    return std::make_unique<feature_flags_packet>(*this);
}