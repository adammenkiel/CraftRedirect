#include <boost/asio.hpp>

#include "protocol/codec/packet_decoder.hpp"

template <typename SyncReadStream>
std::unique_ptr<packet> packet_decoder::readPacket(packet_state state, SyncReadStream stream) {
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
    std::unique_ptr<packet> packet = registry.get_packet_by_id(packet_bound::SERVER, state, packet_id);
    packet->read(input_stream);
    return packet;
}