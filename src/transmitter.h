#pragma once
#include <ace/SOCK_Connector.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>

#include <string>

class Transmitter {
public:
    enum Transfer_Type {
        ACTIVE_MODE = 0,
        PASSIVE_MODE = 1
    };

    Transmitter();
    ~Transmitter();
    int connect(const std::string &ip, uint port);
    int close();
    int send(const std::string &data);

private:
    ACE_SOCK_Stream client_stream_;
    ACE_INET_Addr remote_addr_;
    ACE_SOCK_Connector connector_;
};