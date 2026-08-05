#pragma once
#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_list : public nbt_base {
    public:
        std::vector<std::shared_ptr<nbt_base>> values;
        int get_id();
        std::string to_string();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_list() = default;
        nbt_tag_list() {};
};