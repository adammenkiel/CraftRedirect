#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_int_array : public nbt_base {
    private:
        std::vector<int> values;
    public:
        int get_id();
        std::string to_string();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_int_array() = default;
        nbt_tag_int_array() {};
        nbt_tag_int_array(std::vector<int> values) : values(values) {};
};