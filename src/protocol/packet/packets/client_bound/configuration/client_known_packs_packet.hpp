#pragma once

#include <memory>
#include <array>
#include "protocol/packet/packet.hpp"

class client_known_packs_packet : public packet {
    public:

        uint32_t known_packs_count;
        std::vector<std::array<std::string, 3>> known_packs; // temporary solution - it's good to refactor it into struct

        client_known_packs_packet();

        client_known_packs_packet(
            uint32_t known_packs_count,
            std::vector<std::array<std::string, 3>> known_packs
        );

        ~client_known_packs_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};