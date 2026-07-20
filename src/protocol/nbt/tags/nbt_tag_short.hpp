#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_short : public nbt_base {
    private:
        uint64_t value;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_short() = default;
        nbt_tag_short() {};
        nbt_tag_short(uint64_t value) : value(value) {};
};