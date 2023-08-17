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

std::vector<std::string> split(std::string str, std::string token) {
	std::vector<std::string>result;
	while (str.size()) {
		unsigned long long index = str.find(token);
		if (index != std::string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0)result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}
