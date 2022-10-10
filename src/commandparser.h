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
    typedef std::map<std::string, void (Command_Parser::*)(const std::vector<std::string> &)> Command_Handle;

    Command_Parser();
    ~Command_Parser() {}
    void parsing_data(const char *buf, int len);
    const char *response_data() const;

private:
    void user_handle(const std::vector<std::string> &recv_buffer);
    void pass_handle(const std::vector<std::string> &recv_buffer);
    void pwd_handle(const std::vector<std::string> &recv_buffer);
    void cwd_handle(const std::vector<std::string> &recv_buffer);
    void cdup_handle(const std::vector<std::string> &recv_buffer);
    void port_handle(const std::vector<std::string> &recv_buffer);
    void retr_handle(const std::vector<std::string> &recv_buffer);
    void list_handle(const std::vector<std::string> &recv_buffer);
    void type_handle(const std::vector<std::string> &recv_buffer);
    void stor_handle(const std::vector<std::string> &recv_buffer);
    void pasv_handle(const std::vector<std::string> &recv_buffer);
    void rnfr_handle(const std::vector<std::string> &recv_buffer);
    void rnto_handle(const std::vector<std::string> &recv_buffer);
    void rmd_handle(const std::vector<std::string> &recv_buffer);
    void dele_handle(const std::vector<std::string> &recv_buffer);
    void mkd_handle(const std::vector<std::string> &recv_buffer);
    void quit_handle(const std::vector<std::string> &recv_buffer);
    void cmd_not_implemented_handle();
    void recv_buffer_handle(const char *buff, std::vector<std::string> &recv_buffer);
    void send_buffer_handle(const char *msg);

    std::vector<char> send_buff_;
    static Command_Handle command_;
    static Server_Info info_;
};