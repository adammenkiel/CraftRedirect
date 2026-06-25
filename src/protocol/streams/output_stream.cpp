#include "output_stream.hpp"


void output_stream::writeVarInt(uint32_t value) {
    while (true) {
        if ((value & ~0x7F) == 0) {
            buf.push_back(value & 0x7F);
            return;
        }
        buf.push_back((value & 0x7F) | 0x80);
        value >>= 7;
    }
}

void output_stream::writeString(std::string& text) {
    writeVarInt(text.length());
    for(uint8_t byte : text) {
        buf.push_back(byte);
    }
}

void output_stream::writeByte(uint8_t send) {
    buf.push_back(send);
}

void output_stream::writeUShort(uint16_t send) {
    buf.push_back((send >> 8) & 0xFF);
    buf.push_back(send & 0xFF);
}

void output_stream::writeBytes(std::vector<uint8_t>& data) {
    for(uint8_t data_byte : data) {
        buf.push_back(data_byte);
    }
}

const std::vector<uint8_t>& output_stream::get_buffer() const {
    return buf;
}

void output_stream::writeLong(uint64_t value) {
    for(int i = 0; i < 8; i++) {
        buf.push_back((value >> (7*8 - i*8)) & 0xFF);
    }
}