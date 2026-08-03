#include "protocol/nbt/tags/nbt_tag_compound.hpp"
#include "protocol/nbt/nbt_tag_manager.hpp"

int nbt_tag_compound::get_id() {
    return 10;
}

std::string nbt_tag_compound::to_string() {
    std::string name = "{";
    for(auto elem : tag_map) {
        name += "\""+elem.first + "\": " + elem.second->to_string() + ", ";
    }
    name += "}";
    return name;
}

void nbt_tag_compound::read(input_stream& input) {
    uint8_t id;
    while((id = input.readByte()) != 0) {
        std::string name = input.readUTF();
        auto tag = nbt_tag_manager::get_tag_by_id(id);
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
