#pragma once
#include "protocol/obj/login_success_property.hpp"
//#include "protocol/nbt/nbt_base.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <memory>

class nbt_base;

class input_stream {
    private:
        size_t offset = 0;
        std::vector<uint8_t>& buf;
    public:
        input_stream(std::vector<uint8_t>& bytes);
        uint32_t readableBytes();
        uint32_t readVarInt();
        std::string readString();
        uint8_t readByte();
        uint16_t readUShort();
        std::vector<uint8_t> readBytes(size_t len);
        uint64_t readLong();
        bool readBoolean();
        std::string readUTF();
        std::unique_ptr<nbt_base> readNBT();
        std::vector<uint8_t> readFully();
        std::vector<login_success_property> readProperties();
};