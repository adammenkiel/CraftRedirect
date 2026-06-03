#pragma once

#include "protocol/streams/output_stream.hpp"
#include "session/session.hpp"

class packet_encoder {
    private:
        session& session;
    public:
        void write_packet(packet& packet);
};