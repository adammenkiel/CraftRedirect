
#include "command/commands/test_command.hpp"

void test_command::execute(std::shared_ptr<session> s, std::vector<std::string> args) {
    spdlog::info("Test command working!");
}