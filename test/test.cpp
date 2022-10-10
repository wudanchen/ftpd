#include <iostream>
#include <vector>

#include <pwd.h>
#include <unistd.h>

using namespace std;

void recv_buffer_handle(const char *buff, std::vector<std::string> &recv_buffer)
{
    char *recv_buff = (char *)buff;
    auto *pre_it = recv_buff;
    for(auto *it = recv_buff; *it != '\0'; ++it) {
        if(*it == ' ') {
            recv_buffer.push_back(std::string(pre_it, it));
            pre_it = it + 1;
        }else if(*it == '\r' || *it == '\n') {
            if(pre_it != it) {
                recv_buffer.push_back(std::string(pre_it, it));
            }
            break;
        }
    }
}

int main() {
    getline()
}