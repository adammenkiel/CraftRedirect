#include <memory>

#include "command/commands/online_command.hpp"
#include "protocol/packet/packets/client_bound/play/system_chat_message_packet.hpp"

void online_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    s->sendSingleMessage("§7Players online: §a" + std::to_string(server->sessions.size()));
}