
#include "craft_redirect_server.hpp"

int main() {
    std::shared_ptr<craft_redirect_server> server = std::make_shared<craft_redirect_server>();
    server->run();
    return 0;
}