#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_double : public nbt_base {
    private:
        double value;
    public:
        int get_id();
        std::string to_string();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_double() = default;
        nbt_tag_double() {};
        nbt_tag_double(double value) : value(value) {};
};