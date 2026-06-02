#include "test_connection.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>


#include "streams/output_stream.hpp"

using boost::asio::ip::tcp;

std::vector<uint8_t> generate_handshake(std::string host, uint16_t port) {
    output_stream data;
    data.writeVarInt(0);
    data.writeVarInt(767);
    data.writeString(host);
    data.writeUShort(port);
    data.writeByte(2);

    std::vector data_buffer = data.get_buffer();
    output_stream res;
    res.writeVarInt(data_buffer.size());
    res.writeBytes(data_buffer);
    return res.get_buffer();
}

std::vector<uint8_t> generate_login_start(std::string nickname) {
    output_stream data;
    data.writeVarInt(0);
    data.writeString(nickname);
    for(int i = 0; i < 8; i++)
        data.writeUShort((i * 423434 + 38498348394) & 0xFFFF); // temporiary

    std::vector data_buffer = data.get_buffer();
    output_stream res;
    res.writeVarInt(data_buffer.size());
    res.writeBytes(data_buffer);
    return res.get_buffer();   
}

int test_connection(std::string host, std::string port) {
    
    spdlog::info("Connecting...");
    boost::asio::io_context io;
    tcp::socket socket(io);
    try {
        tcp::resolver resolver(io);
        auto endpoints = resolver.resolve(host, port);

        boost::asio::connect(socket, endpoints);
        
        spdlog::info("Connected! Sending join packets...");
        boost::asio::write(
            socket,
            boost::asio::buffer(generate_handshake("localhost", 25565))
        );
        boost::asio::write(
            socket,
            boost::asio::buffer(generate_login_start("bocik"))
        );

        spdlog::info("Packets sent!");
    } catch (const std::exception& e) {
        spdlog::error("Connection failed!");
    }
    
    return 0;
}