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
    
}