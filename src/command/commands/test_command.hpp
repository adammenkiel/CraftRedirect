#pragma once

#include "command/command.hpp"

class test_command : public command {
    public:
        void execute(std::shared_ptr<session> s, std::vector<std::string> args);
        ~test_command() = default;
};