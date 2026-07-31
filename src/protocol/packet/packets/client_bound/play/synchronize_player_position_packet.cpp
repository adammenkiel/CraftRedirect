#include "protocol/packet/packets/client_bound/play/synchronize_player_position_packet.hpp"

synchronize_player_position_packet::synchronize_player_position_packet(
            double x,
            double y,
            double z,
            float yaw,
            float pitch,
            uint8_t flags,
            uint32_t teleport_id
        ) : 
        x(x),
        y(y),
        z(z),
        yaw(yaw),
        pitch(pitch),
        flags(flags),
        teleport_id(teleport_id) {}

synchronize_player_position_packet::synchronize_player_position_packet() {}

synchronize_player_position_packet::~synchronize_player_position_packet() {}

uint32_t synchronize_player_position_packet::get_packet_id() {
    return 0x40;
}

packet_state synchronize_player_position_packet::get_state() {
    return packet_state::PLAY;
}

void synchronize_player_position_packet::read(input_stream& input) {
    this->x = input.readDouble();
    this->y = input.readDouble();
    this->z = input.readDouble();
    this->yaw = input.readFloat();
    this->pitch = input.readFloat();
    this->flags = input.readByte();
    this->teleport_id = input.readVarInt();
}

void synchronize_player_position_packet::write(output_stream& output) {
    output.writeDouble(this->x);
    output.writeDouble(this->y);
    output.writeDouble(this->z);
    output.writeFloat(this->pitch);
    output.writeFloat(this->yaw);
    output.writeByte(this->flags);
    output.writeVarInt(this->teleport_id);
}

std::unique_ptr<packet> synchronize_player_position_packet::clone() {
    return std::make_unique<synchronize_player_position_packet>(*this);
}