#include "../includes/receiver.hpp"

void
    Receiver::m_diff(const std::string& path)
{
    std::string result("echo ");
    result.append(path);
    result.append(" >> diff");
    system(result.c_str());
    std::string diff("diff ");
    diff.append(REF + path + "result ");
    diff.append(CASE + path + "result ");
    diff.append(">> diff");
    system(diff.c_str());
}

void
    Receiver::m_trunc(const std::string& path)
{
    std::fstream result;
    result.open(CASE + path + "result",
                std::fstream::out | std::fstream::trunc);
    if (result.is_open())
        result.close();
}

void
    Receiver::m_received()
{
    bool   mode  = false;
    t_vstr lines = split(Socket::_buffer, '\n');
    t_vstr nicks = split(lines[1], ',');
    Worker worker[nicks.size()];
    int    size = nicks.size();

    m_trunc(lines[0]);
    if (nicks[0].front() == '!')
    {
        mode = true;
        nicks[0].erase(0, 1);
    }

    for (int i = 0; i < size; ++i)
        worker[i] = Worker(lines[0], nicks[i], lines[i + 2], _port);
    for (int i = 0; i < size; ++i)
        worker[i].run();
    if (mode)
    {
        worker[0]._job = split(lines[lines.size() - 1], '|');
        worker[0].run();
        sleep(1);
    }
    for (int i = 0; i < size; ++i)
        worker[i].flush(true);
    for (int i = 0; i < size; ++i)
        worker[i].quit();
    m_diff(lines[0]);
}

void
    Receiver::m_receive()
{
    if (0 < Socket::receive(_events[Event::_index]))
        m_received();
    // else if (Socket::_result == 0)
    //{
    //     Socket::close(_fd);
    //     Event::remove(_fd);
    //  Event::toggle(Socket::_socket.fd, EV_ENABLE);
    //}
}

void
    Receiver::m_accept()
{
    if (Socket::accept() == -1)
        return;
    Event::add(_fd);
    // Event::toggle(Socket::_socket.fd, EV_DISABLE);
}

void
    Receiver::run()
{
    int count;

    while (true)
    {
        count = Event::kevent();
        for (Event::_index = 0; Event::_index < count; ++Event::_index)
        {
            _fd = _events[Event::_index].ident;
            if (_events[Event::_index].ident == (unsigned)_socket.fd)
                m_accept();
            else if (_events[Event::_index].filter == EVFILT_READ)
                m_receive();
        }
    }
}

Receiver::~Receiver()
{
}

Receiver::Receiver(int port, int target) : _port(target)
{
    Socket::initialize(port);
    Event::initialize(_socket.fd);
    signal(SIGPIPE, SIG_IGN);
}

int
    main(int argc, char** argv)
{
    if (argc != 3)
        return FAILURE;
    Receiver(atoi(argv[1]), atoi(argv[2])).run();
}
