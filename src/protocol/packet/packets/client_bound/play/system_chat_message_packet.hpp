#pragma once

//#include "protocol/nbt/nbt_base.hpp"
#include "protocol/packet/packet.hpp"
#include <array>
#include <memory>

class system_chat_message_packet : public packet {
    public:
        std::shared_ptr<nbt_base> content;
        bool overlay;
        
        system_chat_message_packet(
            std::shared_ptr<nbt_base> content,
            bool overlay
        );

        system_chat_message_packet();

        ~system_chat_message_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};