#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_compound : public nbt_base {
    private:
        
    public:
        int get_id();
        void read(input_stream input);
        void write(output_stream output);
        ~nbt_tag_compound() = default;
};