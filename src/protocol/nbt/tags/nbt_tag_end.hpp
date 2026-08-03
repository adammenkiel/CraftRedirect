#pragma once

#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_end : public nbt_base {
    public:
        int get_id();
        std::string to_string();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_end() = default;
        nbt_tag_end() {};
};