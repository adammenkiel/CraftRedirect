#include "protocol/nbt/nbt_base.hpp"

class nbt_tag_list : public nbt_base {
    private:
        std::vector<std::shared_ptr<nbt_base>> values;
    public:
        int get_id();
        void read(input_stream& input);
        void write(output_stream& output);
        ~nbt_tag_list() = default;
        nbt_tag_list() {};
};