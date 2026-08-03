#include "protocol/nbt/tags/nbt_tag_byte.hpp"

int nbt_tag_byte::get_id() {
    return 1;
}

std::string nbt_tag_byte::to_string() {
    return std::to_string(this->value);
}

void nbt_tag_byte::read(input_stream& input) {
    this->value = input.readByte();
}

void nbt_tag_byte::write(output_stream& output) {
    output.writeByte(value);
}