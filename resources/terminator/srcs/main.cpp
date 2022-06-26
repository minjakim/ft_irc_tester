#include "../includes/client.hpp"
#include "../includes/event.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <sys/_types/_intptr_t.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

std::vector<Client*> clients;
std::string          test_case_name;
std::ifstream        test_case;
std::fstream         reference;
std::string          message;
std::string          buffer;
Client*              client;
Event                event;
int                  result;
int                  count;
int                  port;
int                  target;
bool                 skip = false;

void
    compare_result()
{
    // 로그 읽어와서 비교하기
    std::string test;
    for (int i = 0, size = clients.size(); i < size; ++i)
        test += "\r\n" + clients[i]->nick + "\r\n" + clients[i]->buffer;
    buffer.resize(test.size());
    reference.open("./testcases/reference/" + test_case_name, std::fstream::in);
    if (reference.is_open())
    {
        reference.read(buffer.begin().base(), test.size());
        std::cout << "===== reference ======" << buffer;
        if (buffer == test)
            std::cout << '\n'
                      << test_case_name << ":\033[1;32m ok\033[0m" << std::endl;
        else
        {
            std::cout << "===== test ======" << test;
            std::cout << '\n'
                      << test_case_name << ":\033[1;31m ko\033[0m" << std::endl;
            std::fstream test_file;
            mkdir("./diff", 0755);
            std::string test_dir
                = "./diff/"
                  + test_case_name.substr(0, test_case_name.find_first_of('/'));
            mkdir(test_dir.data(), 0755);
            test_file.open("./diff/" + test_case_name,
                           std::fstream::out | std::fstream::trunc);
            if (test_file.is_open())
            {
                test_file << test;
                test_file.flush();
            }
            std::string diff_str
                = "diff ./testcases/reference/" + test_case_name + " ./diff/"
                  + test_case_name + " > ./diff/" + test_case_name
                  + ".diff || cat ./diff/" + test_case_name + ".diff";
            std::cout << diff_str << std::endl;
            system(diff_str.c_str());
        }
    }
}

void
    make_reference()
{
    reference.open("./testcases/reference/" + test_case_name,
                   std::fstream::out | std::fstream::trunc);
    if (reference.is_open())
    {
        for (int i = 0, size = clients.size(); i < size; ++i)
            reference << "\r\n"
                      << clients[i]->nick << "\r\n"
                      << clients[i]->buffer;
        reference.close();
    }
}

int
    process_testcase()
{
    while ((count = event.kevent()) > 0)
    {
        for (int i = 0; i < count; ++i)
        {
            client = (Client*)event._events[i].udata;
            if (event._events[i].filter == EVFILT_WRITE)
            {
                std::cout << std::setiosflags(std::ios_base::left)
                          << std::setw(9) << client->nick << ": " << message;
                result = write(event._events[i].ident, message.data(),
                               message.size());
                if (result == -1)
                {
                    std::cerr << "write error" << std::endl;
                    return 1;
                }
                event.m_set(client->fd, EVFILT_WRITE, EV_DISABLE, 0, 0, client);
                if (std::getline(test_case, message, ' '))
                {
                    usleep(500000);
                    target = atoi(message.data());
                    event.m_set(clients[target]->fd, EVFILT_WRITE, EV_ENABLE, 0,
                                0, clients[target]);
                    std::getline(test_case, message);
                    message += "\r\n";
                }
            }
            else if (event._events[i].filter == EVFILT_READ)
            {
                buffer.resize(event._events[i].data);
                result = read(event._events[i].ident, (void*)buffer.data(),
                              event._events[i].data);
                if (result == -1)
                {
                    std::cerr << "read error" << std::endl;
                    return 1;
                }
                if (result)
                    client->buffer.append(buffer);
                if (result == 0)
                {
                    close(client->fd);
                    continue;
                }
            }
        }
    }
    return 0;
}

void
    prepare_first_message()
{
    if (std::getline(test_case, message, ' '))
    {
        target = atoi(message.data());
        std::getline(test_case, message);
        event.m_set(clients[target]->fd, EVFILT_WRITE, EV_ENABLE, 0, 0,
                    clients[target]);
        message += "\r\n";
        std::getline(test_case, message, ' ');
    }
}

void
    connect_client_to_server(char* ip)
{
    // 클라이언트를 서버에 연결
    std::getline(test_case, buffer);
    std::istringstream iss(buffer);
    struct kevent      tmp;
    while (std::getline(iss, buffer, ','))
    {
        if (buffer.back() == '!')
        {
            skip = true;
            buffer.pop_back();
        }
        clients.push_back(new Client(buffer, ip, port));
        event.m_set(clients.back()->fd, EVFILT_WRITE, EV_ADD, 0, 0,
                    clients.back());
        event.m_set(clients.back()->fd, EVFILT_READ, EV_ADD, 0, 0,
                    clients.back());
        if (!skip)
        {
            buffer = "pass 6667\r\nnick " + clients.back()->nick
                     + "\r\nuser testuser testhost testserver :realname\r\n";
            while (kevent(event._kqueue, NULL, 0, &tmp, 1, &event.timer))
                if ((int)tmp.ident == clients.back()->fd)
                {
                    if (tmp.filter == EVFILT_WRITE)
                    {
                        result = write(clients.back()->fd, buffer.data(),
                                       buffer.size());
                        if (result)
                            buffer.erase(0, result);
                    }
                    if (tmp.filter == EVFILT_READ)
                    {
                        buffer.resize(tmp.data);
                        if (read(clients.back()->fd, (void*)buffer.data(),
                                 tmp.data))
                            clients.back()->buffer.append(buffer);
                        break;
                    }
                }
            std::cout << std::setiosflags(std::ios_base::left) << std::setw(9)
                      << clients.back()->nick << ": [PASS,NICK,USER]\n";
        }
        event.m_set(clients.back()->fd, EVFILT_WRITE, EV_DISABLE, 0, 0,
                    clients.back());
        skip = false;
    }
}

int
    initialize(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << argv[0] << " <filename> <port> <ip>" << std::endl;
        return 1;
    }
    test_case_name = argv[1];
    test_case.open(test_case_name);
    if (test_case.fail())
    {
        std::cerr << argv[1] << " is not open" << std::endl;
        return 1;
    }
    test_case_name.erase(0, test_case_name.find_first_of('/') + 1);
    test_case_name.erase(0, test_case_name.find_first_of('/') + 1);
    test_case_name.erase(0, test_case_name.find_first_of('/') + 1);
    //연결할 서버 port
    port = atoi(argv[2]);
    // kqueue 생성
    event.initialize();
    return 0;
}

int
    main(int argc, char** argv)
{
    if (initialize(argc, argv))
        return 1;
    connect_client_to_server(argv[3]);
    prepare_first_message();
    if (process_testcase())
        return 1;
    // make_reference();
    compare_result();
}
