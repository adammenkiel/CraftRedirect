#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_byte_array : public nbt_base {
    private:
        std::vector<uint8_t> values;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_byte_array() = default;
        nbt_tag_byte_array() {};
        nbt_tag_byte_array(std::vector<uint8_t> values) : values(values) {};
};