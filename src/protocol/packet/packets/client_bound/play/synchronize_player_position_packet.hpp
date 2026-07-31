#pragma once

#include "protocol/packet/packet.hpp"
#include <array>
#include <memory>

class synchronize_player_position_packet : public packet {
    public:
        double x;
        double y;
        double z;
        float yaw;
        float pitch;
        uint8_t flags;
        uint32_t teleport_id;
        
        synchronize_player_position_packet(
            double x,
            double y,
            double z,
            float yaw,
            float pitch,
            uint8_t flags,
            uint32_t teleport_id
        );

        synchronize_player_position_packet();

        ~synchronize_player_position_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};