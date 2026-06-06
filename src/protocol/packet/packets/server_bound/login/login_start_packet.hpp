#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class login_start_packet : public packet {
    public:
        std::string username;
        std::vector<uint8_t> uuid_bytes;

        
        login_start_packet(
            std::string username,
            std::vector<uint8_t> uuid_bytes
        );

        login_start_packet();

        ~login_start_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};