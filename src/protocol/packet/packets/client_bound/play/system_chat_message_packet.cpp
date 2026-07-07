#include "protocol/packet/packets/client_bound/play/system_chat_message_packet.hpp"

//Temporary not work
//TODO: Add NBT support and fix it!
system_chat_message_packet::system_chat_message_packet(
    //nbt_base content,
    bool overlay
) : 
//    content(content),
    overlay(overlay) {}

system_chat_message_packet::system_chat_message_packet() {}

system_chat_message_packet::~system_chat_message_packet() {}

uint32_t system_chat_message_packet::get_packet_id() {
    return 0x6C;
}

packet_state system_chat_message_packet::get_state() {
    return packet_state::PLAY;
}

void system_chat_message_packet::read(input_stream& input) {
    //content = input.readNBT();
    overlay = input.readBoolean();
}

void system_chat_message_packet::write(output_stream& output) {
    //output.writeNBT(content);
    output.writeBoolean(overlay);
}

std::unique_ptr<packet> system_chat_message_packet::clone() {
    return std::make_unique<system_chat_message_packet>(*this);
}