#pragma once
#include "protocol/packet/packet_state.hpp"
#include "protocol/packet/packet.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session {
    public:
        packet_state state = packet_state::HANDSHAKE;
        tcp::socket& socket;
        bool compression = false;

        session(tcp::socket& socket);

        void handle(packet& packet);

        void sendPacket(packet& packet);
};