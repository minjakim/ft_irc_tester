#include "../includes/client.hpp"
#include "../includes/receiver.hpp"

/* client class constructor and destructor begin */

Client::Client(sockaddr_in addr, int fd) : _addr(addr), _fd(fd)
{
}

Client::Client()
{
}

Client::~Client()
{
}

sockaddr_in
    Client::get_addr()
{
    return _addr;
}

int
    Client::get_fd()
{
    return _fd;
}
