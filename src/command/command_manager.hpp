#pragma once

#include <map>
#include <memory>
#include "command.hpp"

class command_manager {
    private:
        std::map<std::string, std::shared_ptr<command>> command_map;
    public:
        std::vector<std::shared_ptr<command>> commands;
        void register_command(std::shared_ptr<command> command);
        std::shared_ptr<command> get_command(std::string name);
        bool is_command_exists(std::string command_name);
};