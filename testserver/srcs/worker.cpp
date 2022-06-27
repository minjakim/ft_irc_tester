#include "../includes/worker.hpp"
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

void
    Worker::quit()
{
}

void
    Worker::flush(bool mode)
{
    std::fstream result;

    _length          = read(_fd, _buffer, BUFFER_MAX);
    _buffer[_length] = '\0';
    _result.append(_buffer);
    result.open((mode ? CASE : REF) + _path + "result",
                std::fstream::out | std::fstream::app);
    if (result.is_open())
        result << _nick << "\n" << _result << "\n";
    result.close();
}

//기준위치   $_path    ex -> 05_join/07_invite_only_mode_channel
//기록위치   case/$_path/$_nick
//비교위치   ref/$_path/$_nick

void
    Worker::run()
{
    std::string jobs;

    for (int i = 0, size = _job.size(); i < size; ++i)
    {
        _result.append("|" + _job[i]);
        jobs.append(_job[i] + "\r\n");
    }
    write(_fd, jobs.c_str(), jobs.size());
    _result.append("\n\n");
}

void
    Worker::check()
{
    if (_nick.back() != '!')
    {
        std::string buffer = "PASS 6667\r\nNICK " + _nick
                             + "\r\nUSER user host server :real name\r\n";
        write(_fd, buffer.c_str(), buffer.size());
        read(_fd, _buffer, BUFFER_MAX);
        _buffer[0] = '\0';
    }
    else
        _nick.pop_back();
}

Worker::Worker(std::string& path, std::string& nick, std::string& job, int port)
    : _path(path),
      _nick(nick),
      _job(split(job, '|'))
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in socket;
    memset(&socket, 0, sizeof(sockaddr_in));
    socket.sin_family      = AF_INET;
    socket.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket.sin_port        = htons(port);
    if (::connect(_fd, (sockaddr*)&socket, sizeof(sockaddr_in)) == -1)
        std::cout << "link failed" << std::endl;
    check();
}
