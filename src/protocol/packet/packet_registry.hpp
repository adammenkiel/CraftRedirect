#pragma once

#include <unordered_map>
#include "protocol/packet/packet.hpp"
#include "protocol/packet/packet_bound.hpp"

struct packet_info {
    int packet_id;
    packet_bound bound;
    packet_state state;

    bool operator==(const packet_info& other) const {
        return other.packet_id == packet_id && other.bound == bound && other.state == state; 
    }
};

struct packet_info_hash {
    size_t operator()(const packet_info& info) const {
        size_t id = info.packet_id;
        size_t bound = static_cast<int>(info.bound);
        size_t state = static_cast<int>(info.state);

        return (id << 16) ^ (bound << 8) ^ state;
    }
};

class packet_registry {
    public:
        std::unordered_map<packet_info, std::unique_ptr<packet>, packet_info_hash> packets;
        void register_packet(packet_bound bound, packet_state state, packet& packet);
        std::unique_ptr<packet> get_packet_by_id(packet_bound bound, packet_state state, int id);
};