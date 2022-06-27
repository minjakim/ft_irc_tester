#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <fcntl.h>

#define IPV4_MTU_MAX 65535

class Socket
{
  public:
    typedef struct s_socket
    {
        int         fd;
        sockaddr_in addr;
        socklen_t   len;
    } t_socket;

  private:
    void m_create();
    void m_bind(int port);
    void m_listen();
    void m_accept();
    void m_close();
    Socket(const Socket&);
    Socket& operator=(const Socket&);

  protected:
    int         _port;
    t_socket    _socket;
    ssize_t     _result;
    ssize_t     _remain;
    sockaddr_in _addr;
    int         _fd;
    char        _buffer[IPV4_MTU_MAX];

    Socket();
    ~Socket();
    ssize_t receive(const struct kevent& event);
    int     accept();
    void    close(int);
    void    initialize(int port);
};

#endif /* SOCKET_HPP */
