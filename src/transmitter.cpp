#include "transmitter.h"

Transmitter::Transmitter()
{

}

Transmitter::~Transmitter()
{
    close();
}

int Transmitter::connect(const std::string &ip, uint port)
{
    ACE_INET_Addr remote_addr(port, ip.c_str());
    return connector_.connect(client_stream_, remote_addr);
}

int Transmitter::send(const std::string &data)
{
    client_stream_.send(data.c_str(), strlen(data.c_str()) + 1);
}

int Transmitter::close()
{
    client_stream_.close();
}