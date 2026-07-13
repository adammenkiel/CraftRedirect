#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_string : public nbt_base {
    private:
        std::string value;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_string() = default;
        nbt_tag_string() {};
        nbt_tag_string(std::string value) : value(value) {};
};