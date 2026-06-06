#include <spdlog/spdlog.h>

#include "protocol/packet/packet_registry.hpp"
#include "protocol/packet/packet.hpp"

std::unique_ptr<packet> packet_registry::get_packet_by_id(packet_bound bound, packet_state state, int packet_id) {
    auto info = packet_info();

    info.bound = bound;
    info.packet_id = packet_id;
    info.state = state;

    return packets.at(info).get()->clone();
}

void packet_registry::register_packet(packet_bound bound, packet_state state, packet& reg_packet) {
    auto info = packet_info();

    info.bound = bound;
    info.packet_id = reg_packet.get_packet_id();
    info.state = state;

    packets[info] = reg_packet.clone();
    spdlog::info("Registered new packet: {0}", reg_packet.get_packet_id());
}