#pragma once
#include "protocol/packet/packet_state.hpp"
#include "protocol/streams/output_stream.hpp"
#include "protocol/streams/input_stream.hpp"

class packet {
    public:
        virtual ~packet() = default;
        virtual uint32_t get_packet_id() = 0;
        virtual packet_state get_state() = 0;
        virtual void read(input_stream& stream) = 0;
        virtual void write(output_stream& stream) = 0;
};