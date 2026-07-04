#include <iostream>
#include <spdlog/spdlog.h>
#include <typeinfo>
#include <thread>
#include <chrono>

#include "session.hpp"
#include "craft_redirect_server.hpp"
#include "protocol/packet/packets/server_bound/handshake/handshake_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_start_packet.hpp"
#include "protocol/packet/packets/server_bound/status/status_request_packet.hpp"
#include "protocol/packet/packets/server_bound/status/ping_request_packet.hpp"
#include "protocol/packet/packets/server_bound/login/login_acknowledged_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/client_information_packet.hpp"
#include "protocol/packet/packets/server_bound/configuration/known_packs_packet.hpp"

#include "protocol/packet/packets/client_bound/status/status_response_packet.hpp"
#include "protocol/packet/packets/client_bound/status/ping_response_packet.hpp"
#include "protocol/packet/packets/client_bound/login/login_success_packet.hpp"


#include "protocol/packet/unknown_packet.hpp"

session::session(std::shared_ptr<craft_redirect_server> server, tcp::socket& socket) : 
    socket(socket),
    server(server) {}

void session::handle(std::unique_ptr<packet> handled_packet) {
    
    if(auto* received_handshake = dynamic_cast<handshake_packet*>(handled_packet.get())) {
        spdlog::info("Received handshake packet! MC version: {0}, Host: {1}, Port: {2}, State: {3}",
             received_handshake->version_number,
             received_handshake->server_host,
             received_handshake->server_port,
             received_handshake->state
            );
        if(received_handshake->state == 1)
            state = packet_state::STATUS;
        if(received_handshake->state == 2)
            state = packet_state::LOGIN;        
    }

    if(auto* received_login_start = dynamic_cast<login_start_packet*>(handled_packet.get())) {
        spdlog::info("Logged new player: {0}",
            received_login_start->username
        );
        auto uuid = received_login_start->uuid_bytes;
        nickname = received_login_start->username;
        std::vector<login_success_property> properties;


        login_success_packet success_packet = login_success_packet(uuid, nickname, properties, false);
        this->sendPacket(success_packet);
    }

    if(auto* received_request = dynamic_cast<status_request_packet*>(handled_packet.get())) {
        spdlog::info("Request detected!");
        //Simple motd in JSON format.
        status_response_packet packet = status_response_packet(
            R"({"version":{"name":"CraftRedirect/Kuailianjie","protocol":767},"description":"       §8§k||| §4CraftRedirect §8§k|||\n§cYour proxy server for minecraft","players":{"max":0,"online":500}})"
        );
        this->sendPacket(packet);
    }

    if(auto* received_ping_request = dynamic_cast<ping_request_packet*>(handled_packet.get())) {
        spdlog::info("Ping response");
        ping_response_packet packet = ping_response_packet(received_ping_request->time);
        this->sendPacket(packet);
    }

    if(auto* received_acknowledge = dynamic_cast<login_acknowledged_packet*>(handled_packet.get())) {
        spdlog::info("Received login acknowledged packet! State set into CONFIGURATION!");
        this->state = packet_state::CONFIGURATION;
    }


    // temporary solutions below!!
    if(auto* received_client_information = dynamic_cast<client_information_packet*>(handled_packet.get())) {
        unknown_packet payload = unknown_packet(packet_state::CONFIGURATION, 1,
             std::vector<uint8_t>({15, 109, 105, 110, 101, 99, 114, 97, 102, 116, 58, 98, 114, 97, 110, 100, 5, 80, 97, 112, 101, 114}));
        this->sendPacket(payload);
        unknown_packet feature_flags = unknown_packet(packet_state::CONFIGURATION, 0x0C,
            std::vector<uint8_t>({1, 17, 109, 105, 110, 101, 99, 114, 97, 102, 116, 58, 118, 97, 110, 105, 108, 108, 97}));
        this->sendPacket(feature_flags);
        unknown_packet known_flags = unknown_packet(packet_state::CONFIGURATION, 0x0E,
            std::vector<uint8_t>({1, 9, 109, 105, 110, 101, 99, 114, 97, 102, 116, 4, 99, 111, 114, 101, 6, 49, 46, 50, 49, 46, 49}));
        this->sendPacket(known_flags);

        spdlog::info("Received client info!");
    }

    if(auto* known_packs = dynamic_cast<known_packs_packet*>(handled_packet.get())) {
        for(auto& packet : server->config_packets) {
            if(auto* received_unknown_packet = dynamic_cast<unknown_packet*>(packet.get())) {
                spdlog::info("Packet ID: {0}, size: {1}", received_unknown_packet->get_packet_id(), received_unknown_packet->packet_bytes.size());
            }
            this->sendPacket(*packet->clone());
        }
        unknown_packet success = unknown_packet(packet_state::CONFIGURATION, 3, std::vector<uint8_t>({}));
        this->sendPacket(success);
        spdlog::info("Known packs packet received correctly!");
    }

    if(auto* received_unknown_packet = dynamic_cast<unknown_packet*>(handled_packet.get())) {
        std::string result = "";
        for(uint8_t byte : received_unknown_packet->packet_bytes) {
            result += std::to_string(static_cast<int>(byte)) + ", ";
        }
        spdlog::info("Received unknown packet {0} bytes: {1}", received_unknown_packet->get_packet_id(), result);
    }
}

void session::sendPacket(packet& packet) {
    output_stream data_stream;
    data_stream.writeVarInt(packet.get_packet_id());
    packet.write(data_stream);
    std::vector<uint8_t> data_buffer = data_stream.get_buffer();
    
    output_stream packet_stream;
    packet_stream.writeVarInt(data_buffer.size());
    packet_stream.writeBytes(data_buffer);
    
    boost::asio::write(
        socket,
        boost::asio::buffer(packet_stream.get_buffer())
    );
}