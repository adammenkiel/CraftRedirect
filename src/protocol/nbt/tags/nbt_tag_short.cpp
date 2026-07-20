#include "protocol/nbt/tags/nbt_tag_short.hpp"

int nbt_tag_short::get_id() {
    return 2;
}

void nbt_tag_short::read(input_stream& input) {
    this->value = input.readLong();
}

void nbt_tag_short::write(output_stream& output) {
    output.writeLong(value);
}