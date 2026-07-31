#pragma once

#include "protocol/packet/packet.hpp"
#include <array>
#include <memory>

class player_abilities_packet : public packet {
    public:
        uint8_t flags;
        float flying_speed;
        float field_of_view_modifier;
        
        player_abilities_packet(
            uint8_t flags,
            float flying_speed,
            float field_of_view_modifier
        );

        player_abilities_packet();

        ~player_abilities_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};