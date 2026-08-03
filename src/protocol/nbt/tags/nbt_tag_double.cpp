#include "protocol/nbt/tags/nbt_tag_double.hpp"

int nbt_tag_double::get_id() {
    return 6;
}

std::string nbt_tag_double::to_string() {
    return std::to_string(this->value);
}

void nbt_tag_double::read(input_stream& input) {
    this->value = input.readDouble();
}

void nbt_tag_double::write(output_stream& output) {
    output.writeDouble(value);
}