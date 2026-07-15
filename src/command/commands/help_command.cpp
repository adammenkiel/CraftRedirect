#include <memory>

#include "command/commands/help_command.hpp"

void help_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    s->sendSingleMessage("§7Server commands:");
    for(auto& line : server->command_map) {
        s->sendSingleMessage("§7- §c/" + line.first);
    }
}