#pragma once

#include "protocol/packet/packet.hpp"
#include <array>

class chat_command_packet : public packet {
    public:
        std::string command_label;

        
        chat_command_packet(
            std::string command_label
        );

        chat_command_packet();

        ~chat_command_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};