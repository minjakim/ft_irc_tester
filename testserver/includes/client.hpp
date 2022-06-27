#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "resources.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>

class Client
{
  private:
    sockaddr_in _addr;
    int         _fd;

  public:
    Client(sockaddr_in client_addr, int client_fd);
    Client();
    ~Client();

    sockaddr_in get_addr();
    int         get_fd();
};

#endif /* CLIENT_HPP */
