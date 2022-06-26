#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  public:
    int         fd;
    int         port;
    std::string nick;
    std::string buffer;

    Client(std::string, char*, int);
    ~Client();
};

#endif /* CLIENT_HPP */
