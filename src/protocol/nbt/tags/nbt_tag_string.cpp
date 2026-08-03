#include "protocol/nbt/tags/nbt_tag_string.hpp"

int nbt_tag_string::get_id() {
    return 8;
}

std::string nbt_tag_string::to_string() {
    return "\"" + this->value + "\"";
}

void nbt_tag_string::read(input_stream& input) {
    this->value = input.readUTF();
}

void nbt_tag_string::write(output_stream& output) {
    output.writeUTF(value);
}