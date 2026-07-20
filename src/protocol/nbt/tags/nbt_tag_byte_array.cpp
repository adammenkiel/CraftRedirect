#include "protocol/nbt/tags/nbt_tag_byte_array.hpp"

int nbt_tag_byte_array::get_id() {
    return 7;
}

void nbt_tag_byte_array::read(input_stream& input) {
    size_t len = input.readInt();
    this->values = input.readBytes(len);
}

void nbt_tag_byte_array::write(output_stream& output) {
    output.writeInt(this->values.size());
    output.writeBytes(this->values);
}