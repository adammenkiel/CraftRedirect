#pragma once
#include "protocol/streams/input_stream.hpp"
#include "protocol/streams/output_stream.hpp"

class nbt_base {
    public:
        virtual int get_id() = 0;
        virtual void read(input_stream& input) = 0;
        virtual void write(output_stream& output) = 0;
        std::unique_ptr<nbt_base> get_tag_by_id(int id) {
            return NULL;
        }
        ~nbt_base() = default;
};