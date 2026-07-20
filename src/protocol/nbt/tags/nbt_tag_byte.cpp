#include "protocol/nbt/tags/nbt_tag_byte.hpp"

int nbt_tag_byte::get_id() {
    return 1;
}

void nbt_tag_byte::read(input_stream& input) {
    this->value = input.readByte();
}

void nbt_tag_byte::write(output_stream& output) {
    output.writeByte(value);
}