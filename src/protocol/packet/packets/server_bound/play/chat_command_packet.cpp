#include "protocol/packet/packets/server_bound/play/chat_command_packet.hpp"

chat_command_packet::chat_command_packet(
    std::string command_label
) : 
    command_label(command_label) {}

chat_command_packet::chat_command_packet() {}

chat_command_packet::~chat_command_packet() {}

uint32_t chat_command_packet::get_packet_id() {
    return 4;
}

packet_state chat_command_packet::get_state() {
    return packet_state::PLAY;
}

void chat_command_packet::read(input_stream& input) {
    command_label = input.readString();
}

void chat_command_packet::write(output_stream& output) {
    output.writeString(command_label);
}

std::unique_ptr<packet> chat_command_packet::clone() {
    return std::make_unique<chat_command_packet>(*this);
}