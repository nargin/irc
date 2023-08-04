#include "Server.hpp"
#include "Client.hpp"

bool isValidNick(std::map<int, Client>_clients, std::string nick) {
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        if (it->second.getNickname() == nick)
            return false;
    return true;
}