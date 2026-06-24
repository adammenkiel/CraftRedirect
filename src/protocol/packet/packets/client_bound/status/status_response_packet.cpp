#include "protocol/packet/packets/client_bound/status/status_response_packet.hpp"

status_response_packet::status_response_packet(
    std::string json_response
) : 
json_response(json_response) {}

status_response_packet::status_response_packet() {}

status_response_packet::~status_response_packet() {}

uint32_t status_response_packet::get_packet_id() {
    return 0;
}

packet_state status_response_packet::get_state() {
    return packet_state::STATUS;
}

void status_response_packet::read(input_stream& input) {
    json_response = input.readString();
}

void status_response_packet::write(output_stream& output) {
    output.writeString(json_response);
}

std::unique_ptr<packet> status_response_packet::clone() {
    return std::make_unique<status_response_packet>(*this);
}