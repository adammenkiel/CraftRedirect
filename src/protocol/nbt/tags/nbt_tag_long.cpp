#include "protocol/nbt/tags/nbt_tag_long.hpp"

int nbt_tag_long::get_id() {
    return 4;
}

std::string nbt_tag_long::to_string() {
    return std::to_string(this->value);
}

void nbt_tag_long::read(input_stream& input) {
    this->value = input.readLong();
}

void nbt_tag_long::write(output_stream& output) {
    output.writeLong(value);
}