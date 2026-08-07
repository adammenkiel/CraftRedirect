#include "command_manager.hpp"
#include "command/command.hpp"

void command_manager::register_command(std::shared_ptr<command> command) {
    this->commands.push_back(command);
    this->command_map[command->command_name] = command;
    for(std::string alias : command->aliases) {
        this->command_map[alias] = command;
    }
}

std::shared_ptr<command> command_manager::get_command(std::string name) {
    return this->command_map[name];
}

bool command_manager::is_command_exists(std::string command_name) {
    return !(this->command_map.find(command_name) == this->command_map.end());
}