#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class client_keep_alive_packet : public packet {
    public:
        uint64_t value;

        
        client_keep_alive_packet(
            uint64_t value
        );

        client_keep_alive_packet();

        ~client_keep_alive_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};