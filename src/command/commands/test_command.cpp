#include <memory>

#include "command/commands/test_command.hpp"
#include "protocol/packet/packets/client_bound/play/system_chat_message_packet.hpp"

void test_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    //system_chat_message_packet chat_message = system_chat_message_packet(R"({text: "Test command working"})", false);
    //s->sendPacket(chat_message);
    nbt_tag_compound compound;
    compound.tag_map["text"] = std::make_shared<nbt_tag_string>("Hello world");
    system_chat_message_packet chat_message = system_chat_message_packet(std::make_shared<nbt_tag_compound>(compound), false);
    s->sendPacket(chat_message);
    spdlog::info("Test command working!");
}