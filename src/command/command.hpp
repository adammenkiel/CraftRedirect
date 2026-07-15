#pragma once
#include <session/session.hpp>
#include <vector>

class session;
class craft_redirect_server;

class command {
    public:
        std::shared_ptr<craft_redirect_server> server;
        explicit command(std::shared_ptr<craft_redirect_server> server) : server(server) {};
        virtual void execute(std::shared_ptr<session> s, std::vector<std::string> args) = 0;
        virtual ~command() = default;
};