#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"
#include "test/test_connection.hpp"

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_context io;
    tcp::endpoint endpoint(tcp::v4(), 25565);
    tcp::acceptor acceptor(io);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    
    std::vector<std::thread> threads;

    while(true) {
        tcp::socket socket = acceptor.accept();
        spdlog::info("Socket connecting");
        threads.emplace_back([socket = std::move(socket)]() mutable {
            while(true) {
                uint32_t packetLengthTemp = 0;
                int position = 0;
                uint8_t currentByte;

                while (true) {
                    boost::asio::read(socket, boost::asio::buffer(&currentByte, 1));
                    packetLengthTemp |= (currentByte & 0x7F) << position;
                    if ((currentByte & 0x80) == 0) break;
                    position += 7;
                    if (position >= 32) throw std::runtime_error("VarInt is too big"); // temporary
                }
                std::vector<uint8_t> packetBytes(packetLengthTemp);
                boost::asio::read(socket, boost::asio::buffer(packetBytes));
                input_stream input_stream(packetBytes);
                
            }
        });
    }
    //test_connection("localhost", "25565");
    return 0;
}