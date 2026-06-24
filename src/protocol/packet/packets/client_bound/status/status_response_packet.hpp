#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class status_response_packet : public packet {
    public:
        std::string json_response;
        
        status_response_packet(
            std::string json_response
        );

        status_response_packet();

        ~status_response_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};