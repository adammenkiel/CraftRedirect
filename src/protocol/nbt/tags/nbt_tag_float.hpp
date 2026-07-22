#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_float : public nbt_base {
    private:
        float value;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_float() = default;
        nbt_tag_float() {};
        nbt_tag_float(float value) : value(value) {};
};