#include "input_stream.hpp"

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

std::vector<uint8_t> input_stream::readBytes(size_t len) {
    if(len + offset > buf.size()) {
        throw std::runtime_error("String out of bound");
    }
    std::vector<uint8_t> copyBytes(
        buf.begin() + offset,
        buf.begin() + offset + len
    );

    offset += len;
    return copyBytes;
}

uint32_t input_stream::readableBytes() {
    return buf.size() - offset;
}

uint16_t input_stream::readUShort() {
    uint16_t first = readByte();
    uint16_t second = readByte();
    return (first << 8) | second;
}

uint64_t input_stream::readLong() {
    uint64_t number = 0;
    for(int i = 0; i < 8; i++) {
        number = (number << 8) | readByte();
    }
    return number;
}

bool input_stream::readBoolean() {
    return readByte() != 0;
}

std::string input_stream::readUTF() {
    size_t size = readUShort();
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

std::unique_ptr<nbt_base> input_stream::readNBT() {
    
}

std::vector<login_success_property> input_stream::readProperties() {
    std::vector<login_success_property> properties;
    uint32_t size = this->readVarInt();
    for(int i = 0; i < size; i++) {
        std::string property_name = this->readString();
        std::string property_value = this->readString();
        bool is_signed = this->readBoolean();
        std::string signature = (is_signed ? this->readString() : "");
        login_success_property property(property_name, property_value, is_signed, signature);
        properties.push_back(property);
    }    
    return properties;
}

std::vector<uint8_t> input_stream::readFully() {
    return this->readBytes(this->buf.size() - offset);
}