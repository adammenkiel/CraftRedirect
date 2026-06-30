#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class client_information_packet : public packet {
    public:
        std::string locale;
        uint8_t view_distance;
        uint32_t chat_mode;
        bool chat_colors;
        uint8_t displayed_skin_parts;
        uint32_t main_hand;
        bool enable_text_filtering;
        bool allow_server_listings;
        
        client_information_packet(
            std::string locale,
            uint8_t view_distance,
            uint32_t chat_mode,
            bool chat_colors,
            uint8_t displayed_skin_parts,
            uint32_t main_hand,
            bool enable_text_filtering,
            bool allow_server_listings
        );

        client_information_packet();

        ~client_information_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};