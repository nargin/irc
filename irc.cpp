#include "irc.hpp"

IRC::IRC() {}

IRC::IRC(int port, std::string password) : _port(port), _pass(password) {}
IRC::~IRC() {}

int IRC::socketisation() {
    IRC::sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }
    return 0;
}

void IRC::connect() {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(this->_port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error connecting" << std::endl;
        return;
    }
}