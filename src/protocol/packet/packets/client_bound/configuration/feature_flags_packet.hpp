#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class feature_flags_packet : public packet {
    public:
        uint32_t len;
        std::vector<std::string> flags;

        
        feature_flags_packet(
            uint32_t len,
            std::vector<std::string> flags
        );

        feature_flags_packet();

        ~feature_flags_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};