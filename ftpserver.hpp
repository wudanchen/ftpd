#pragma once

class Ftp_Server {
public:
    Ftp_Server();
    ~Ftp_Server();

private:
    int port_;
    int ip_;
};