#include "Server.hpp"
#include "Client.hpp"

bool isValidNick(std::map<int, Client>_clients, std::string nick) {
    if (nick.length() < 1 || nick.length() > 16)
        return false;
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        if (it->second.getNickname() == nick)
            return false;
    return true;
}