#include "protocol/nbt/tags/nbt_tag_byte_array.hpp"

int nbt_tag_byte_array::get_id() {
    return 7;
}

std::string nbt_tag_byte_array::to_string() {
    std::string array_text = "[";
    for(auto val : this->values) {
        array_text += std::to_string(val) + ", ";
    }
    array_text += "]";
    return array_text;
}

void nbt_tag_byte_array::read(input_stream& input) {
    size_t len = input.readInt();
    this->values = input.readBytes(len);
}

void nbt_tag_byte_array::write(output_stream& output) {
    output.writeInt(this->values.size());
    output.writeBytes(this->values);
}