/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-01 17:35:28
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-07 01:21:31
 * @FilePath: /ftpd/ftpserver.h
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */

#pragma once
#include "threadpool.h"

class Ftp_Server {
public:
    Ftp_Server(int port);
    ~Ftp_Server();
    int run_loop();

private:
    int port_;
    Thread_Pool thread_pool_;
};