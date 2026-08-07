#include "protocol/nbt/tags/nbt_tag_short.hpp"

int nbt_tag_short::get_id() {
    return 2;
}

std::string nbt_tag_short::to_string() {
    return std::to_string(this->value);
}

void nbt_tag_short::read(input_stream& input) {
    this->value = input.readUShort();
}

void nbt_tag_short::write(output_stream& output) {
    output.writeUShort(value);
}