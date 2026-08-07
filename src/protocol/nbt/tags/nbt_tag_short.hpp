#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_short : public nbt_base {
    private:
        uint16_t value;
    public:
        int get_id();
        std::string to_string();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_short() = default;
        nbt_tag_short() {};
        nbt_tag_short(uint16_t value) : value(value) {};
};