#include "../includes/event.hpp"

void
    Event::m_set(int     identity,
                 short   filter,
                 u_short flags,
                 u_int   fflags,
                 int     data,
                 void*   udata)
{
    struct kevent kev;
    EV_SET(&kev, identity, filter, flags, fflags, data, udata);
    ::kevent(_kqueue, &kev, 1, NULL, 0, NULL);
}

void
    Event::toggle(int EVFILT_TYPE)
{
    m_set(_events[_index].ident, EVFILT_TYPE, EV_DISABLE, 0, 0,
          (Client*)_events[_index].udata);
    m_set(_events[_index].ident,
          (EVFILT_TYPE == EVFILT_READ ? EVFILT_WRITE : EVFILT_READ), EV_ENABLE,
          0, 0, (Client*)_events[_index].udata);
}

void
    Event::toggle(int socket_fd, int EV_TYPE)
{
    m_set(socket_fd, EVFILT_WRITE, EV_TYPE, 0, 0, NULL);
}

void
    Event::remove(int fd)
{
    m_set(fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    m_set(fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
}

void
    Event::add(int fd)
{
    m_set(fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    m_set(fd, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL);
}

int
    Event::kevent()
{
    _count = ::kevent(_kqueue, NULL, 0, _events, EVENTS_MAX, NULL);
    return (_count);
}

int
    Event::kevent(const timespec ts)
{
    _count = ::kevent(_kqueue, NULL, 0, _events, EVENTS_MAX, NULL);
    return (_count);
}

void
    Event::initialize(int socket)
{
    if ((_kqueue = ::kqueue()) == -1)
        exit(FAILURE);
    m_set(socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
}

void
    Event::initialize()
{
    if ((_kqueue = ::kqueue()) == -1)
        exit(FAILURE);
}

Event::Event()
{
}

Event::~Event()
{
}
