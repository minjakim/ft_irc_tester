#include "../includes/socket.hpp"
#include "../includes/client.hpp"
#include <fcntl.h>
#include <sys/event.h>
#include <unistd.h>

Socket::~Socket()
{
}

void
    Socket::m_close()
{
    ::close(_fd);
}

void
    Socket::m_create()
{
    if ((_socket.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        exit(EXIT_FAILURE);
    }
    int toggle = 1;
    setsockopt(_socket.fd, SOL_SOCKET, SO_REUSEPORT, (const void*)&toggle,
               sizeof(toggle));
}

void
    Socket::m_bind(int port)
{
    memset(&_socket.addr, 0, sizeof(sockaddr_in));
    _socket.addr.sin_family      = AF_INET;
    _socket.addr.sin_addr.s_addr = INADDR_ANY;
    _socket.addr.sin_port        = htons(port);

    if (bind(_socket.fd, (struct sockaddr*)&_socket.addr, sizeof(sockaddr_in))
        == -1)
    {
        exit(EXIT_FAILURE);
    }
}

void
    Socket::m_listen()
{
    if (listen(_socket.fd, SOMAXCONN) == -1)
    {
        exit(EXIT_FAILURE);
    }
    fcntl(_socket.fd, F_SETFL, O_NONBLOCK);
}

ssize_t
    Socket::receive(const struct kevent& event)
{
    _fd     = event.ident;
    _result = recv(_fd, _buffer, event.data, 0);

    if (_result == 0)
        m_close();
    return _result;
}

int
    Socket::accept()
{
    if ((_fd = ::accept(_socket.fd, (sockaddr*)(&_addr), &_socket.len)) == -1)
        ;
    else
        fcntl(_fd, F_SETFL, O_NONBLOCK);
    return _fd;
}

void
    Socket::close(int fd)
{
    ::close(fd);
}

void
    Socket::initialize(int port)
{
    m_create();
    m_bind(port);
    m_listen();
}

Socket::Socket()
{
    _socket.len = sizeof(_socket.addr);
    _socket.fd  = -1;
}
