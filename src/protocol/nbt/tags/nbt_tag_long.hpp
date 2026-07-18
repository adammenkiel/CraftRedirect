#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_long : public nbt_base {
    private:
        uint64_t value;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_long() = default;
        nbt_tag_long() {};
        nbt_tag_long(uint64_t value) : value(value) {};
};