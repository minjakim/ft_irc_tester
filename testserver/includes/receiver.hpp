#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "event.hpp"
#include "resources.hpp"
#include "socket.hpp"
#include "worker.hpp"

class Receiver : public Socket, public Event
{
  private:
    Receiver(const Receiver&);
    Receiver& operator=(const Receiver&);

    void m_accept();
    void m_receive();
    void m_received();
    void m_trunc(const std::string&);
    void m_disconnected(std::string reason = "");
    void m_disconnect(std::string reason = "");
    void m_diff(const std::string& path);
    void m_send();

    Client _client;
    int    _port;

  public:
    Receiver(int, int);
    ~Receiver();
    void run();
};
#endif /* RECEIVER_HPP */
