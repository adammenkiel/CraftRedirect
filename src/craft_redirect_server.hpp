#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <memory>
#include <map>
#include <command/command.hpp>

#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"
#include "protocol/packet/packet_registry.hpp"
#include "protocol/codec/packet_decoder.hpp"

#include "session/session.hpp"

class session;
class command;

class craft_redirect_server : public std::enable_shared_from_this<craft_redirect_server> {
    private:
        void registerAllPackets();
        void loadRegistryPackets();
        void startServer();
        void registerCommands();
    public:
        packet_registry packets;
        std::vector<std::shared_ptr<session>> sessions;
        std::vector<std::unique_ptr<packet>> config_packets;
        std::map<std::string, std::shared_ptr<command>> command_map;
        void run();
};