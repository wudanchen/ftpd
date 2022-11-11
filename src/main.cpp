#include "ftpserver.h"
#include <iostream>

using namespace std;

int main(int arg, char *agrv[]) {
    if(arg != 2) {
        cout << "server parameters are less than two." << endl;
        return -1;
    }
    
    Ftp_Server server(atoi(agrv[1]));
    return server.run_loop();
}
//aaaa
