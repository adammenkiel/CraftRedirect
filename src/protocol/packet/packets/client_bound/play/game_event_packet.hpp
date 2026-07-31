#pragma once

#include "protocol/packet/packet.hpp"
#include <array>
#include <memory>

class game_event_packet : public packet {
    public:
        uint8_t event;
        float value;
        
        game_event_packet(
            uint8_t event,
            float value
        );

        game_event_packet();

        ~game_event_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};