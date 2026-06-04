#pragma once
#include <memory>
#include "protocol/packet/packet.hpp"

class handshake_packet : public packet {
    public:

        uint32_t version_number;
        std::string server_host;
        uint32_t server_port;
        uint8_t state;

        handshake_packet(
            uint32_t version_number,
            std::string server_host,
            uint32_t server_port,
            uint8_t state
        );

        ~handshake_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};