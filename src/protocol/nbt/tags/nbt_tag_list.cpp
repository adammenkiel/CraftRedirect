#include "protocol/nbt/tags/nbt_tag_list.hpp"
#include "protocol/nbt/nbt_tag_manager.hpp"

int nbt_tag_list::get_id() {
    return 9;
}

std::string nbt_tag_list::to_string() {
    std::string array_text = "[";
    for(auto val : this->values) {
        array_text += val->to_string() + ", ";
    }
    return array_text + "]";
}

void nbt_tag_list::read(input_stream& input) {
    uint8_t id = input.readByte();
    uint32_t size = input.readInt();
    for(int i = 0; i < size; i++) {
        auto base = nbt_tag_manager::get_tag_by_id(id);
        base->read(input);
        this->values.push_back(std::move(base));
    }
}

void nbt_tag_list::write(output_stream& output) {
    output.writeByte(this->values.size() == 0 ? 0 : this->values[0]->get_id());
    output.writeInt(this->values.size());
    for(auto base : this->values) {
        base->write(output);
    }
}