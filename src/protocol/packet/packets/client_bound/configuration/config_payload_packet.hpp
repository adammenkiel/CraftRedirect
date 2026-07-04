#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class config_payload_packet : public packet {
    public:
        std::string tag;
        std::vector<uint8_t> data;

        
        config_payload_packet(
            std::string tag,
            std::vector<uint8_t> data
        );

        config_payload_packet();

        ~config_payload_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};