#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#define REF 0
#define DIR "./testcases/"

#if REF == 0
#define RESULT "result"
#else
#define RESULT "ref"
#endif

#define PORT_MAX 65535

#define CHANNEL_USER_MAX   42
#define CHANNEL_LENGTH_MAX 50
#define CLIENT_CAHNNEL_MAX 10
#define NICK_LENGTH_MAX    9
#define EVENTS_MAX         1024
#define SPECIALCHAR        "[]\\`-^{|}"
#define CHSTRING           " ,\r\n\7"
#define CONNECTION         4
#define DELIMITER          ','

typedef std::vector<std::string> t_vstr;

static t_vstr
    split(const std::string& params, char delimiter)
{
    t_vstr             splited;
    std::istringstream iss(params);
    std::string        element;

    while (std::getline(iss, element, delimiter))
        splited.push_back(element);
    return splited;
}

enum e_exit
{
    SUCCESS,
    FAILURE,
};

#endif /* RESOURCES_HPP */
