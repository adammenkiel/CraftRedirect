#include "protocol/nbt/tags/nbt_tag_float.hpp"

int nbt_tag_float::get_id() {
    return 5;
}

void nbt_tag_float::read(input_stream& input) {
    this->value = input.readFloat();
}

void nbt_tag_float::write(output_stream& output) {
    output.writeFloat(value);
}