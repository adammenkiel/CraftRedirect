#pragma once
#include <session/session.hpp>

class command {
    virtual void execute(session s, std::string* args);
};