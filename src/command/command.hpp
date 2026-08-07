#pragma once
#include <vector>
#include <string>

class session;
class craft_redirect_server;

class command {
    public:
        std::string command_name;
        std::vector<std::string> aliases;
        std::string description;

        std::shared_ptr<craft_redirect_server> server;
        
        explicit command(
            std::shared_ptr<craft_redirect_server> server,
            std::string command_name,
            std::vector<std::string> aliases,
            std::string description
        ) : server(server),
            command_name(command_name),
            aliases(aliases),
            description(description) {};
        
        virtual void execute(std::shared_ptr<session> s, std::vector<std::string> args) = 0;
        virtual ~command() = default;
};