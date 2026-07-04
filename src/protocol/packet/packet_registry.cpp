#include <spdlog/spdlog.h>

#include "protocol/packet/packet_registry.hpp"
#include "protocol/packet/packet.hpp"
#include "protocol/packet/unknown_packet.hpp"

std::unique_ptr<packet> packet_registry::get_packet_by_id(packet_bound bound, packet_state state, int packet_id) {
    auto info = packet_info();

    info.bound = bound;
    info.packet_id = packet_id;
    info.state = state;

    if((packets.find(info) == packets.end())) {
        unknown_packet unknown = unknown_packet(state, packet_id);
        return unknown.clone();
    }
    return std::move(packets.at(info).get()->clone());

}

void packet_registry::register_packet(packet_bound bound, packet_state state, packet& reg_packet) {
    auto info = packet_info();

    info.bound = bound;
    info.packet_id = reg_packet.get_packet_id();
    info.state = state;

    packets[info] = reg_packet.clone();
}