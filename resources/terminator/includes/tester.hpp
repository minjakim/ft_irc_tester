
#include "event.hpp"
#include "socket.hpp"

class Tester : public Socket, public Event
{

  public:
    Tester();
    void run(int);
};
