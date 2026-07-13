#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <memory>
#include "protocol/obj/login_success_property.hpp"
//#include "protocol/nbt/nbt_base.hpp"

class nbt_base; 

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
        void writeProperties(std::vector<login_success_property> properties);
        void writeBoolean(bool boolean);
        void writeUTF(std::string text);
        void writeNBT(std::shared_ptr<nbt_base> nbt);
        const std::vector<uint8_t>& get_buffer() const;
};