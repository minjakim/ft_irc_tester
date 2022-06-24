#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  public:
    int         fd;
    std::string nick;
    int         port;
    std::string buffer;

    Client(std::string, char*, int);
    ~Client();
};

#endif /* CLIENT_HPP */
