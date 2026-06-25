#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

class output_stream {
    private:
        std::vector<uint8_t> buf;
    public:
        void writeVarInt(uint32_t value);
        void writeString(std::string& text);
        void writeByte(uint8_t send);
        void writeUShort(uint16_t send);
        void writeBytes(std::vector<uint8_t>& data);
        void writeLong(uint64_t value);
        const std::vector<uint8_t>& get_buffer() const;
};