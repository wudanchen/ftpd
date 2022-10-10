/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-09 14:56:30
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-09 15:24:57
 * @FilePath: /ftpd/src/serverinfo.h
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#pragma once

#include <map>
#include <string>
#include <list>

class Server_Info {
public:
    Server_Info();
    ~Server_Info();
    bool check_logged_in(const std::string &account);
    bool check_user_name(const std::string &user_name);
    bool check_password(const std::string &user_name, const std::string &passward);
private:
    std::map<std::string, std::string> account_password_map_;
    std::list<std::string> logged_account_;
};