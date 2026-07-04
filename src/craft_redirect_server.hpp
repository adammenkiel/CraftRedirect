#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <memory>

#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"
#include "protocol/packet/packet_registry.hpp"
#include "protocol/codec/packet_decoder.hpp"

#include "session/session.hpp"

class session;

class craft_redirect_server : public std::enable_shared_from_this<craft_redirect_server> {
    private:
        void registerAllPackets();
        void loadRegistryPackets();
        void startServer();
    public:
        packet_registry packets;
        std::vector<std::shared_ptr<session>> sessions;
        std::vector<std::unique_ptr<packet>> config_packets;
        void run();
};