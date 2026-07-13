#pragma once

#include "command/command.hpp"

#include "protocol/nbt/nbt_base.hpp"
#include "protocol/nbt/tags/nbt_tag_string.hpp"
#include "protocol/nbt/tags/nbt_tag_compound.hpp"

class test_command : public command {
    public:
        void execute(std::shared_ptr<session> s, std::vector<std::string> args);
        ~test_command() = default;
};