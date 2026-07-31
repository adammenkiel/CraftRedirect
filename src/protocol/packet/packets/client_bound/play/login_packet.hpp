#pragma once

#include "protocol/packet/packet.hpp"
#include "session/position/position.hpp"

#include <array>

class login_packet : public packet {
    public:
        uint32_t entity_id;
        bool is_hardcore;
        std::vector<std::string> dimension_names;
        uint32_t max_players;
        uint32_t view_distance;
        uint32_t simulation_distance;
        bool reduced_debug_info;
        bool enable_respawn_screen;
        bool do_limited_crafting;
        uint32_t dimension_type;
        std::string dimension_name;
        uint64_t hashed_seed;
        uint8_t game_mode;
        uint8_t previous_game_mode;
        bool is_debug;
        bool is_flat;
        bool has_death_location;
        std::string death_dimension_name; // optional
        position death_location; // change to location class or structure!
        uint32_t portal_cooldown;
        bool enforces_secure_chat;
        
        login_packet(
            uint32_t entity_id,
            bool is_hardcore,
            std::vector<std::string> dimension_names,
            uint32_t max_players,
            uint32_t view_distance,
            uint32_t simulation_distance,
            bool reduced_debug_info,
            bool enable_respawn_screen,
            bool do_limited_crafting,
            uint32_t dimension_type,
            std::string dimension_name,
            uint64_t hashed_seed,
            uint8_t game_mode,
            uint8_t previous_game_mode,
            bool is_debug,
            bool is_flat,
            std::string death_dimension_name, // optional
            position death_location, // optional
            uint32_t portal_cooldown,
            bool enforces_secure_chat
        );

        login_packet(
            uint32_t entity_id,
            bool is_hardcore,
            std::vector<std::string> dimension_names,
            uint32_t max_players,
            uint32_t view_distance,
            uint32_t simulation_distance,
            bool reduced_debug_info,
            bool enable_respawn_screen,
            bool do_limited_crafting,
            uint32_t dimension_type,
            std::string dimension_name,
            uint64_t hashed_seed,
            uint8_t game_mode,
            uint8_t previous_game_mode,
            bool is_debug,
            bool is_flat,
            uint32_t portal_cooldown,
            bool enforces_secure_chat
        );

        login_packet();

        ~login_packet() override;

        void read(input_stream&) override;

        void write(output_stream&) override;

        uint32_t get_packet_id() override;

        packet_state get_state() override;

        std::unique_ptr<packet> clone() override;
};