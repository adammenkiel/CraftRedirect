#pragma once
#include <session/session.hpp>
#include <vector>

class session;

class command {
    public:
        virtual void execute(std::shared_ptr<session> s, std::vector<std::string> args) = 0;
        virtual ~command() = default;
};