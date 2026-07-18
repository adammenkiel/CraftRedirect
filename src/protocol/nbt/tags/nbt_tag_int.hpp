#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_int : public nbt_base {
    private:
        uint32_t value;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_int() = default;
        nbt_tag_int() {};
        nbt_tag_int(uint32_t value) : value(value) {};
};