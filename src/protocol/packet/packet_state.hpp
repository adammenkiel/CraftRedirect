#pragma once

enum class packet_state {
    HANDSHAKE,
    LOGIN,
    STATUS,
    CONFIGURATION,
    PLAY
};