#include "input_stream.hpp"
#include <boost/asio.hpp>

input_stream::input_stream(std::vector<uint8_t>& vector) : buf(vector) {}

uint32_t input_stream::readVarInt() {
    uint32_t value = 0;
    int position = 0;
    uint8_t currentByte;

    while (true) {
        currentByte = readByte();
        value |= (currentByte & 0x7F) << position;

        if ((currentByte & 0x80) == 0) break;

        position += 7;

        if (position >= 32) throw std::runtime_error("VarInt is too big");
    }

    return value;
}

uint8_t input_stream::readByte() {
    if(offset >= buf.size()) throw std::runtime_error("Bad structure of packet");
    return buf[offset++];
}

std::string input_stream::readString() {
    size_t size = readVarInt();
    if(size + offset > buf.size()) {
        throw std::runtime_error("String out of bound");
    }
    std::string textstr = std::string(
        buf.begin() + offset,
        buf.begin() + offset + size
    );
    offset += size;
    return textstr;
}