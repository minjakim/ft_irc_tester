#ifndef EVENT_HPP
#define EVENT_HPP

#include "client.hpp"
#include <sys/event.h>
#include <sys/types.h>

class Client;

class Event
{
  public:
    Event(const Event&);
    Event&        operator=(const Event&);
    void          m_set(int     identity,
                        short   filter,
                        u_short flags,
                        u_int   fflags,
                        int     data,
                        void*   udata);
    int           _kqueue;
    int           _count;
    struct kevent _events[EVENTS_MAX];
    int           _index;
    void          toggle(int EVFILT_TYPE);
    void          toggle(int, int EV_TYPE);
    void          initialize(int socket);
    void          remove(int fd);
    void          add(int fd);
    int           kevent();
    int           kevent(const timespec ts);
    Event();
    ~Event();
    void initialize();
    Event(int);
};

#endif /* EVENT_HPP */
