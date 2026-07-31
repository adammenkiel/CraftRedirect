#include "protocol/packet/packets/client_bound/play/player_abilities_packet.hpp"

player_abilities_packet::player_abilities_packet(
            uint8_t flags,
            float flying_speed,
            float field_of_view_modifier
        ) : 
        flags(flags),
        flying_speed(flying_speed),
        field_of_view_modifier(field_of_view_modifier) {}

player_abilities_packet::player_abilities_packet() {}

player_abilities_packet::~player_abilities_packet() {}

uint32_t player_abilities_packet::get_packet_id() {
    return 0x38;
}

packet_state player_abilities_packet::get_state() {
    return packet_state::PLAY;
}

void player_abilities_packet::read(input_stream& input) {
    this->flags = input.readByte();
    this->flying_speed = input.readFloat();
    this->field_of_view_modifier = input.readFloat();
}

void player_abilities_packet::write(output_stream& output) {
    output.writeByte(this->flags);
    output.writeFloat(this->flying_speed);
    output.writeFloat(this->field_of_view_modifier);
}

std::unique_ptr<packet> player_abilities_packet::clone() {
    return std::make_unique<player_abilities_packet>(*this);
}