#pragma once

#include "protocol/packet/packet.hpp"
#include "protocol/obj/login_success_property.hpp"
#include <array>

class login_success_packet : public packet {
    public:
        std::vector<uint8_t> uuid_bytes;
        std::string username;
        std::vector<login_success_property> properties;
        bool strict_error_handling;

        
        login_success_packet(
            std::vector<uint8_t> uuid_bytes,
            std::string username,
            std::vector<login_success_property> properties,
            bool strict_error_handling
        );

        login_success_packet();

        ~login_success_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};