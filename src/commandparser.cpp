/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-09 14:08:37
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-10 15:52:34
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
#include <sstream>

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
    : send_buff_(msg_new_user)
{
    
}

void Command_Parser::parsing_data(const char *buf, int len)
{
    std::vector<std::string> recv_buffer;
    recv_buffer_handle(buf, recv_buffer);
    std::string command_str = recv_buffer.front();
    std::transform (command_str.begin (), command_str.end(), command_str.begin(), ::toupper);
    ACE_DEBUG((LM_DEBUG, "recv command str : %s\n", command_str.data()));
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
    if(recv_buffer.size() != 2) {
        send_buffer_handle(msg_login_fail);
        return;
    }
    if(info_.check_logged_in(recv_buffer.at(1))) {
        send_buffer_handle(msg_login_success);
    }else if(info_.check_user_name(recv_buffer.at(1))) {
        info_.set_user(recv_buffer.at(1));
        send_buffer_handle(msg_user_require_pass);
    }else {
        send_buffer_handle(msg_login_fail);
    }
}

void Command_Parser::pass_handle(const std::vector<std::string> &recv_buffer)
{
    if(recv_buffer.size() != 2) {
        send_buffer_handle(msg_user_require_pass);
        return;
    }
    if(info_.check_password(info_.user(), recv_buffer.at(1))) {
        info_.set_status(true);
        send_buffer_handle(msg_login_success);
    }else {
        send_buffer_handle(msg_login_fail);
    }
}

void Command_Parser::pwd_handle(const std::vector<std::string> &recv_buffer)
{
    if(info_.current_dir().empty()) {
        send_buffer_handle(msg_action_not_taken);
        return;
    }
    char msg[512] = {0};
    sprintf(msg, msg_pwd_success, info_.current_dir().c_str());
    send_buffer_handle(msg);
}

void Command_Parser::cwd_handle(const std::vector<std::string> &recv_buffer)
{
    if(recv_buffer.size() != 2) {
        send_buffer_handle(msg_login_fail);
        return;
    }
    cmd_not_implemented_handle();
}

void Command_Parser::cdup_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::port_handle(const std::vector<std::string> &recv_buffer)
{
    std::vector<std::string> spilt_str = spilt(recv_buffer.at(1), ',');
    if(spilt_str.size() != 6) {
        send_buffer_handle(msg_syntax_error);
        return;
    }
    info_.set_connect_ip(spilt_str.at(0) + "." + spilt_str.at(1) + "." + spilt_str.at(2) + "." + spilt_str.at(3));
    int p1 = atoi(spilt_str.at(4).c_str());
    int p2 = atoi(spilt_str.at(5).c_str());
    info_.set_connect_port(p1 * 256 + p2);
    send_buffer_handle(msg_common_success);
}

void Command_Parser::retr_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::list_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::type_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::stor_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::pasv_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::rnfr_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::rnto_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::rmd_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::dele_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::mkd_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::quit_handle(const std::vector<std::string> &recv_buffer)
{
    cmd_not_implemented_handle();
}

void Command_Parser::cmd_not_implemented_handle()
{
    send_buffer_handle(msg_cmd_not_implemented);
}

void Command_Parser::recv_buffer_handle(const char *buff, std::vector<std::string> &recv_buffer)
{
    char *recv_buff = (char *)buff;
    auto *pre_it = recv_buff;
    for(auto *it = recv_buff; *it != '\0'; ++it) {
        if(*it == ' ') {
            recv_buffer.push_back(std::string(pre_it, it));
            pre_it = it + 1;
        }else if(*it == '\r' || *it == '\n') {
            if(pre_it != it) 
                recv_buffer.push_back(std::string(pre_it, it));
            break;
        }
    }
}

void Command_Parser::send_buffer_handle(const std::string &msg)
{
    send_buff_.assign(msg);
}

std::vector<std::string> Command_Parser::spilt(const std::string &str, const char separator)
{
    std::vector<std::string> result_str;
    auto pre_it = str.begin();
    for(auto it = str.begin(); it != str.end(); ++it) {
        if(*it == separator) {
            result_str.push_back(std::string(pre_it, it));
            pre_it = it + 1;
        }
    }
    if(pre_it != str.end()) {
        result_str.push_back(std::string(pre_it, str.end()));
    }
    return result_str;
}