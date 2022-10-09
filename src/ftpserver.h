/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-01 17:35:28
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-09 13:58:27
 * @FilePath: /ftpd/src/ftpserver.h
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */

#pragma once

class Ftp_Server {
public:
    explicit Ftp_Server(int port);
    ~Ftp_Server();
    int run_loop();

private:
    int port_;
};