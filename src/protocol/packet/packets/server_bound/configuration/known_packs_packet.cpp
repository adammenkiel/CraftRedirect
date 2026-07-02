#include "protocol/packet/packets/server_bound/configuration/known_packs_packet.hpp"

known_packs_packet::known_packs_packet(
            uint32_t known_packs_count,
            std::vector<std::array<std::string, 3>> known_packs
        ) : 
        known_packs_count(known_packs_count),
        known_packs(known_packs) {}

known_packs_packet::known_packs_packet() {}

known_packs_packet::~known_packs_packet() {}

uint32_t known_packs_packet::get_packet_id() {
    return 7;
}

packet_state known_packs_packet::get_state() {
    return packet_state::CONFIGURATION;
}

void known_packs_packet::read(input_stream& input) {
    known_packs_count = input.readVarInt();
    for(int i = 0; i < known_packs_count; i++) {

        std::array<std::string, 3> pack = {
            input.readString(),
            input.readString(),
            input.readString()
        };
        known_packs.push_back(pack);
    }
}

void known_packs_packet::write(output_stream& output) {
    output.writeVarInt(known_packs_count);
    for(int i = 0; i < known_packs_count; i++) {
        output.writeString(known_packs[i][0]);
        output.writeString(known_packs[i][1]);
        output.writeString(known_packs[i][2]);
    }
}

std::unique_ptr<packet> known_packs_packet::clone() {
    return std::make_unique<known_packs_packet>(*this);
}