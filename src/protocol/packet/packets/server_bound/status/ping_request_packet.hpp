#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class ping_request_packet : public packet {
    public:
        uint64_t time;
        
        ping_request_packet(
            std::uint64_t time
        );

        ping_request_packet();

        ~ping_request_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};