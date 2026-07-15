#pragma once

#include "craft_redirect_server.hpp"
#include "command/command.hpp"

class online_command : public command {
    public:
        explicit online_command(std::shared_ptr<craft_redirect_server> server) : command(server) {};
        void execute(std::shared_ptr<session> s, std::vector<std::string> args);
        ~online_command() = default;
};