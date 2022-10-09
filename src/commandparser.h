/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-09 15:01:45
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-09 16:30:54
 * @FilePath: /ftpd/src/commandparser.h
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#pragma once
#include "serverinfo.h"

#include <vector>
#include <functional>
#include <map>

class Command_Parser {
public:
    Command_Parser();
    ~Command_Parser() {}
    void parsing_data(const char *buf, int len);
    const char *response_data() const;

private:
    void user_handle();
    void pass_handle();
    void pwd_handle();
    void cwd_handle();
    void cdup_handle();
    void port_handle();
    void retr_handle();
    void list_handle();
    void type_handle();
    void stor_handle();
    void pasv_handle();
    void rnfr_handle();
    void rnto_handle();
    void rmd_handle();
    void dele_handle();
    void mkd_handle();
    void quit_handle();
    void cmd_not_implemented_handle();
    void recv_buffer_handle(const char *buff);
    void send_buffer_handle(const char *msg);

    std::vector<char> send_buff_;
    std::vector<std::string> recv_buffer_;
    static std::map<std::string, void (Command_Parser::*)()> command_;
    static Server_Info info_;
};