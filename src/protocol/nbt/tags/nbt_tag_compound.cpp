#include "protocol/nbt/tags/nbt_tag_compound.hpp"

int nbt_tag_compound::get_id() {
    return 10;
}
void nbt_tag_compound::read(input_stream& input) {
    uint8_t id;
    while((id = input.readByte()) != 0) {
        std::string name = input.readUTF();
        std::unique_ptr<nbt_base> tag = this->get_tag_by_id(id);
        tag->read(input);
        tag_map[name] = std::move(tag);
    }
}
void nbt_tag_compound::write(output_stream& output) {
    for(auto& pair : tag_map) {
        auto& value = pair.second;
        output.writeByte(value->get_id());
        if(value->get_id() != 0) {
            output.writeUTF(pair.first);
            value->write(output);
        }
    }
    output.writeByte(0);
}
