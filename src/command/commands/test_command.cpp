#include <memory>

#include "command/commands/test_command.hpp"
#include "protocol/packet/packets/client_bound/play/system_chat_message_packet.hpp"

void test_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    s->sendSingleMessage("§cTest command §aworks§c!");
}