#include "protocol/nbt/tags/nbt_tag_int.hpp"

int nbt_tag_int::get_id() {
    return 3;
}

std::string nbt_tag_int::to_string() {
    return std::to_string(this->value);
}

void nbt_tag_int::read(input_stream& input) {
    this->value = input.readInt();
}

void nbt_tag_int::write(output_stream& output) {
    output.writeInt(value);
}