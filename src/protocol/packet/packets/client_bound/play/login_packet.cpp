#include "protocol/packet/packets/client_bound/play/login_packet.hpp"

login_packet::login_packet(
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
            bool has_death_location,
            std::string death_dimension_name, // optional
            uint64_t death_location, // optional
            uint32_t portal_cooldown,
            bool enforces_secure_chat
) : 
    entity_id(entity_id),
    is_hardcore(is_hardcore),
    dimension_names(dimension_names),
    max_players(max_players),
    view_distance(view_distance),
    simulation_distance(simulation_distance),
    reduced_debug_info(reduced_debug_info),
    enable_respawn_screen(enable_respawn_screen),
    do_limited_crafting(do_limited_crafting),
    dimension_type(dimension_type),
    dimension_name(dimension_name),
    hashed_seed(hashed_seed),
    game_mode(game_mode),
    previous_game_mode(previous_game_mode),
    is_debug(is_debug),
    is_flat(is_flat),
    has_death_location(has_death_location),
    death_dimension_name(death_dimension_name), // optional
    death_location(death_location), // optional
    portal_cooldown(portal_cooldown),
    enforces_secure_chat(enforces_secure_chat) {}

login_packet::login_packet() {}

login_packet::~login_packet() {}

uint32_t login_packet::get_packet_id() {
    return 0x2B;
}

packet_state login_packet::get_state() {
    return packet_state::PLAY;
}

void login_packet::read(input_stream& input) {
    //TODO: finish it
}

void login_packet::write(output_stream& output) {
    //TODO: finish it
}

std::unique_ptr<packet> login_packet::clone() {
    return std::make_unique<login_packet>(*this);
}