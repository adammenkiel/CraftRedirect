#include <memory>

#include "command/commands/online_command.hpp"

void online_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    s->sendSingleMessage("§7Players online: §a" + std::to_string(server->sessions.size()));
}