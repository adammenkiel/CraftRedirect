#include <memory>

#include "command/commands/help_command.hpp"

void help_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    s->sendSingleMessage("§7Server commands:");
    for(std::shared_ptr<command> command : server->command_manager.commands) {
        s->sendSingleMessage("§7- §c/" + command->command_name + "§8 - §7" + command->description);
    }
}