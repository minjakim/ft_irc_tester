#include "event.hpp"
#include "resources.hpp"
#include "socket.hpp"

#define BUFFER_MAX 4096

class Worker
{
  public:
    int         _fd;
    t_vstr      _job;
    char        _buffer[BUFFER_MAX];
    ssize_t     _length;
    std::string _result;
    std::string _nick;
    std::string _path;
    void        check();
    Worker(){};
    ~Worker(){};
    Worker(std::string&, std::string&, std::string&, int);
    void run();
    void flush(bool mode);
    void quit();
};
