/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-01 17:50:33
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-06 15:00:33
 * @FilePath: /ftpd/main.cpp
 * @Description: 服务器主函数设计
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
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
