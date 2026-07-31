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
            std::string death_dimension_name, // optional
            position death_location, // optional
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
    has_death_location(true),
    death_dimension_name(death_dimension_name), // optional
    death_location(death_location), // optional
    portal_cooldown(portal_cooldown),
    enforces_secure_chat(enforces_secure_chat) {}

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
    has_death_location(false),
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
    this->entity_id = input.readInt();
    this->is_hardcore = input.readBoolean();
    int len = input.readVarInt();
    for(int i = 0; i < len; i++) dimension_names.push_back(input.readString());
    this->max_players = input.readVarInt();
    this->view_distance = input.readVarInt();
    this->simulation_distance = input.readVarInt();
    this->reduced_debug_info = input.readBoolean();
    this->enable_respawn_screen = input.readBoolean();
    this->do_limited_crafting = input.readBoolean();
    this->dimension_type = input.readVarInt();
    this->dimension_name = input.readString();
    this->hashed_seed = input.readLong();
    this->game_mode = input.readByte();
    this->previous_game_mode = input.readByte();
    this->is_debug = input.readBoolean();
    this->is_flat = input.readBoolean();
    this->has_death_location = input.readBoolean();
    if(this->has_death_location) {
        this->death_dimension_name = input.readString();
        this->death_location = input.readPosition();
    }
    this->portal_cooldown = input.readVarInt();
    this->enforces_secure_chat = input.readBoolean();
}

void login_packet::write(output_stream& output) {
    output.writeInt(this->entity_id);
    output.writeBoolean(this->is_hardcore);
    output.writeVarInt(this->dimension_names.size());
    for(std::string d_name : dimension_names) output.writeString(d_name);
    output.writeVarInt(this->max_players);
    output.writeVarInt(this->view_distance);
    output.writeVarInt(this->simulation_distance);
    output.writeBoolean(this->reduced_debug_info);
    output.writeBoolean(this->enable_respawn_screen);
    output.writeBoolean(this->do_limited_crafting);
    output.writeVarInt(this->dimension_type);
    output.writeString(this->dimension_name);
    output.writeLong(this->hashed_seed);
    output.writeByte(this->game_mode);
    output.writeByte(this->previous_game_mode);
    output.writeBoolean(this->is_debug);
    output.writeBoolean(this->is_flat);
    output.writeBoolean(this->has_death_location);
    if(this->has_death_location) {
        output.writeString(this->death_dimension_name);
        output.writePosition(this->death_location);
    }
    output.writeVarInt(this->portal_cooldown);
    output.writeBoolean(this->enforces_secure_chat);
}

std::unique_ptr<packet> login_packet::clone() {
    return std::make_unique<login_packet>(*this);
}