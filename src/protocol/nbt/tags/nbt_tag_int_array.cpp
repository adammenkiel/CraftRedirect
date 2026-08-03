#include "protocol/nbt/tags/nbt_tag_int_array.hpp"

int nbt_tag_int_array::get_id() {
    return 11;
}

std::string nbt_tag_int_array::to_string() {
    std::string array_text = "[";
    for(auto val : this->values) {
        array_text += std::to_string(val) + ", ";
    }
    return array_text + "]";
}

void nbt_tag_int_array::read(input_stream& input) {
    int len = input.readInt();
    for(int i = 0; i < len; i++) {
        values.push_back(input.readInt());
    }
}

void nbt_tag_int_array::write(output_stream& output) {
    output.writeInt(values.size());
    for(int val : values) {
        output.writeInt(val);
    }
}