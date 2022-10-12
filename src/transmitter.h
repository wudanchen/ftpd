#pragma once
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>

#include <string>
class User_Info;
class Transmitter {
public:
    enum Transfer_Type {
        ACTIVE_MODE = 0,
        PASSIVE_MODE = 1
    };

    explicit Transmitter(uint port = 8888);
    ~Transmitter();
    int open_listen();
    inline const ACE_INET_Addr &get_addr() const { return addr_; }
    int start(const User_Info &info);
    int send(const std::string &data);
    int recv(std::string &data);
    void end();

private:
    int connect(const std::string &ip, uint port);

    ACE_SOCK_Stream client_stream_;
    ACE_SOCK_Connector connector_;
    ACE_SOCK_Acceptor acceptor_;
    ACE_INET_Addr addr_;
};