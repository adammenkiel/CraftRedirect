#pragma once

#include <memory>
#include "protocol/packet/packet.hpp"
#include "protocol/packet/packet_registry.hpp"

class packet_decoder {
    private:
        packet_registry& registry;
    public:
        packet_decoder(packet_registry& registry) : registry(registry) {};
        template <typename SyncReadStream>
        std::unique_ptr<packet> readPacket(packet_state state, SyncReadStream inputStream);
};