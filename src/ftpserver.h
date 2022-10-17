#pragma once

class Ftp_Server {
public:
    explicit Ftp_Server(int port);
    ~Ftp_Server();
    int run_loop();

private:
    int port_;
};
