/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-09 14:08:37
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-09 16:46:33
 * @FilePath: /ftpd/src/commandparser.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include "commandparser.h"
#include "constants.h"

#include <ace/Log_Msg.h>
#include <cstring>
#include <algorithm>

Command_Parser::Command_Handle Command_Parser::command_ =
{
    { "USER", &Command_Parser::user_handle },
    { "PASS", &Command_Parser::pass_handle },
    { "QUIT", &Command_Parser::quit_handle },
    { "PWD", &Command_Parser::pwd_handle },
    { "CWD", &Command_Parser::cwd_handle },
    { "CDUP", &Command_Parser::cdup_handle },
    { "PORT", &Command_Parser::port_handle },
    { "RETR", &Command_Parser::retr_handle },
    { "LIST", &Command_Parser::list_handle },
    { "TYPE", &Command_Parser::type_handle },
    { "STOR", &Command_Parser::stor_handle },
    { "PASV", &Command_Parser::pasv_handle },
    { "RNFR", &Command_Parser::rnfr_handle },
    { "RNTO", &Command_Parser::rnto_handle },
    { "RMD", &Command_Parser::rmd_handle },
    { "DELE", &Command_Parser::dele_handle },
    { "MKD", &Command_Parser::mkd_handle }
};

Command_Parser::Command_Parser()
{
}

void Command_Parser::parsing_data(const char *buf, int len)
{
    std::vector<std::string> recv_buffer = {0};
    recv_buffer_handle(buf, recv_buffer);
    std::string command_str = recv_buffer.front();
    ACE_DEBUG((LM_DEBUG, "recv command str : %s\n", command_str));
    auto it = command_.find(command_str);
    if(it != command_.end()) {
        (this->*(it->second))(recv_buffer);
    }else {
        cmd_not_implemented_handle();
    }
}

const char *Command_Parser::response_data() const
{
    return send_buff_.data();
}

void Command_Parser::user_handle(const std::vector<std::string> &recv_buffer)
{
    if(recv_buffer.at(1).empty()) {
        send_buffer_handle(msg_login_fail);
        return;
    }
    if(info_.check_logged_in(recv_buffer.at(1))) {
        send_buffer_handle(msg_login_success);
    }else if(info_.check_user_name(recv_buffer.at(1))) {
        send_buffer_handle(msg_user_require_pass);
    }else {
        send_buffer_handle(msg_login_fail);
    }
}

void Command_Parser::pass_handle(const std::vector<std::string> &recv_buffer)
{
    
}

void Command_Parser::pwd_handle(const std::vector<std::string> &recv_buffer)
{
    
}

void Command_Parser::cmd_not_implemented_handle()
{
    send_buffer_handle(msg_cmd_not_implemented);
}

void Command_Parser::recv_buffer_handle(const char *buff, std::vector<std::string> &recv_buffer)
{

}

void Command_Parser::send_buffer_handle(const char *msg)
{
    send_buff_.clear();
    send_buff_.resize(strlen(msg) + 1);
    std::copy(send_buff_.begin(), send_buff_.end(), msg);
}