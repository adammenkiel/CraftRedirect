#include "protocol/nbt/tags/nbt_tag_long.hpp"

int nbt_tag_long::get_id() {
    return 4;
}

void nbt_tag_long::read(input_stream& input) {
    this->value = input.readLong();
}

void nbt_tag_long::write(output_stream& output) {
    output.writeLong(value);
}