#include "protocol/packet/packets/server_bound/configuration/client_information_packet.hpp"

client_information_packet::client_information_packet(
            std::string locale,
            uint8_t view_distance,
            uint32_t chat_mode,
            bool chat_colors,
            uint8_t displayed_skin_parts,
            uint32_t main_hand,
            bool enable_text_filtering,
            bool allow_server_listings
        ) : 
        locale(locale),
        view_distance(view_distance),
        chat_mode(chat_mode),
        chat_colors(chat_colors),
        displayed_skin_parts(displayed_skin_parts),
        main_hand(main_hand),
        enable_text_filtering(enable_text_filtering),
        allow_server_listings(allow_server_listings) {}

client_information_packet::client_information_packet() {}

client_information_packet::~client_information_packet() {}

uint32_t client_information_packet::get_packet_id() {
    return 0;
}

packet_state client_information_packet::get_state() {
    return packet_state::CONFIGURATION;
}

void client_information_packet::read(input_stream& input) {
        locale = input.readString();
        view_distance = input.readByte();
        chat_mode = input.readVarInt();
        chat_colors = input.readBoolean();
        displayed_skin_parts = input.readByte();
        main_hand = input.readVarInt();
        enable_text_filtering = input.readBoolean();
        allow_server_listings = input.readBoolean();
}

void client_information_packet::write(output_stream& output) {
    output.writeString(locale);
    output.writeByte(view_distance);
    output.writeVarInt(chat_mode);
    output.writeBoolean(chat_colors);
    output.writeByte(displayed_skin_parts);
    output.writeVarInt(main_hand);
    output.writeBoolean(enable_text_filtering);
    output.writeBoolean(allow_server_listings);
}

std::unique_ptr<packet> client_information_packet::clone() {
    return std::make_unique<client_information_packet>(*this);
}