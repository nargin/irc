#include "irc.hpp"

IRC::IRC() {}

IRC::IRC(int port, std::string password) : _port(port), _pass(password) { IRC::connect(); }
IRC::~IRC() {}

void IRC::connect() {
    std::cout << "Connecting to port " << this->_port << " with password " << this->_pass << std::endl;
}