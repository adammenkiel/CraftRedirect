#pragma once

#include <memory>
#include "protocol/packet/packet.hpp"
#include "protocol/packet/packet_registry.hpp"

class packet_decoder {
    private:
        std::shared_ptr<packet_registry> registry;
    public:
        packet_decoder(std::shared_ptr<packet_registry> registry) : registry(registry) {};
        
        template <typename SyncReadStream>
        std::unique_ptr<packet> readPacket(packet_bound bound, packet_state state, SyncReadStream& stream) {
            uint32_t packetLengthTemp = 0;
            int position = 0;
            uint8_t currentByte;
        
            while (true) {
                boost::asio::read(stream, boost::asio::buffer(&currentByte, 1));
                packetLengthTemp |= (currentByte & 0x7F) << position;
                if ((currentByte & 0x80) == 0) break;
                position += 7;
                if (position >= 32) throw std::runtime_error("VarInt is too big"); // temporary
            }
            std::vector<uint8_t> packetBytes(packetLengthTemp);
            boost::asio::read(stream, boost::asio::buffer(packetBytes));
            input_stream input_stream(packetBytes);
        
            uint32_t packet_id = input_stream.readVarInt(); //temporary
            std::unique_ptr<packet> packet = registry->get_packet_by_id(bound, state, packet_id);
            packet->read(input_stream);
            return packet;
        }
};