#pragma once
#include <unordered_map>
#include "protocol/packet/packet.hpp"
#include "protocol/packet/packet_bound.hpp"

struct packet_info { // hash and equals is required
    int packet_id;
    packet_bound bound;
    packet_state state;
};

class packet_registry {
    public:
        std::unordered_map<packet_info, packet> packets;
        void register_packet(packet_bound bound, packet_state state, packet& packet);
        std::unique_ptr<packet> get_packet_by_id(packet_bound bound, packet_state state, int id);
};