#include "transmitter.h"
#include "userinfo.h"

#include <ace/Log_Msg.h>

Transmitter::Transmitter(uint port)
    : addr_(port)
{

}

Transmitter::~Transmitter()
{
}

int Transmitter::open_listen()
{
    return acceptor_.open(addr_);
}

int Transmitter::start(const User_Info &info)
{
    if(info.mode() == ACTIVE_MODE) {
        return connect(info.connect_ip(), info.connect_port());
    }

    ACE_Time_Value timeout (ACE_DEFAULT_TIMEOUT);
    return acceptor_.accept(client_stream_, nullptr, &timeout);
}

int Transmitter::connect(const std::string &ip, uint port)
{
    ACE_INET_Addr remote_addr(port, ip.c_str());
    return connector_.connect(client_stream_, remote_addr);
}

int Transmitter::send(const std::string &data)
{
    return client_stream_.send(data.c_str(), strlen(data.c_str()) + 1);
}

int Transmitter::recv(std::string &data)
{
    char buf[1024] = {0};
    while (true) {
        ssize_t ret = client_stream_.recv(buf, sizeof(buf));
        if(ret < 0) {
            if(ACE_ERRNO_GET == EAGAIN || ACE_ERRNO_GET == EWOULDBLOCK) {
                return 0;
            }
            return -1;
        }else if (ret == 0) {
            ACE_DEBUG((LM_DEBUG, "connect closed.\n"));
            return -1;
        }

        data.append(std::string(buf, buf + ret));
    }

    return 0;
}

void Transmitter::end()
{
    acceptor_.close();
    client_stream_.close();
}
