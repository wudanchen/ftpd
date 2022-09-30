#pragma once
#include <ace/ACE.h>
#include <ace/Thread.h>
class Ftp_Server {
public:
    Ftp_Server();
    ~Ftp_Server();

private:
    int port_;
    int ip_;
};