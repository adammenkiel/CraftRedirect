#pragma once
#include <boost/asio.hpp>

#include "protocol/packet/packet_state.hpp"
#include "protocol/packet/packet.hpp"
#include "craft_redirect_server.hpp"

class craft_redirect_server;

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
    public:
        packet_state state = packet_state::HANDSHAKE;
        tcp::socket& socket;
        std::shared_ptr<craft_redirect_server> server;
        std::string nickname = "";
        bool compression = false;

        session(std::shared_ptr<craft_redirect_server> server, tcp::socket& socket);

        void handle(std::unique_ptr<packet> packet);

        void sendPacket(packet& packet);

        void disconnect();
};