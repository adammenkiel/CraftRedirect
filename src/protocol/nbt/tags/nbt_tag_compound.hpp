#include "protocol/nbt/nbt_base.hpp"
#include <map>

class nbt_tag_compound : public nbt_base {
    private:
        std::map<std::string, std::unique_ptr<nbt_base>> tag_map;
    public:
        int get_id();
        void read(input_stream input);
        void write(output_stream output);
        ~nbt_tag_compound() = default;
};