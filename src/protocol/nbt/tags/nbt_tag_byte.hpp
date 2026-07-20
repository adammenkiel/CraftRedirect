#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_byte : public nbt_base {
    private:
        uint8_t value;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_byte() = default;
        nbt_tag_byte() {};
        nbt_tag_byte(uint8_t value) : value(value) {};
};