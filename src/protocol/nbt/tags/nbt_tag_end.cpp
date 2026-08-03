#include "protocol/nbt/tags/nbt_tag_end.hpp"

int nbt_tag_end::get_id() {
    return 0;
}

std::string nbt_tag_end::to_string() {
    return "";
}

void nbt_tag_end::read(input_stream& input) {}

void nbt_tag_end::write(output_stream& output) {}