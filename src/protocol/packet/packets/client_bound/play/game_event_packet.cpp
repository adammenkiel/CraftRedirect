#include "protocol/packet/packets/client_bound/play/game_event_packet.hpp"

game_event_packet::game_event_packet(
            uint8_t event,
            float value
        ) : 
        event(event),
        value(value) {}

game_event_packet::game_event_packet() {}

game_event_packet::~game_event_packet() {}

uint32_t game_event_packet::get_packet_id() {
    return 0x22;
}

packet_state game_event_packet::get_state() {
    return packet_state::PLAY;
}

void game_event_packet::read(input_stream& input) {
    this->event = input.readByte();
    this->value = input.readFloat();
}

void game_event_packet::write(output_stream& output) {
    output.writeByte(this->event);
    output.writeFloat(this->value);
}

std::unique_ptr<packet> game_event_packet::clone() {
    return std::make_unique<game_event_packet>(*this);
}