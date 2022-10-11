#pragma once

#include <map>
#include <list>

class User_Info {
public:
    User_Info();
    ~User_Info();

    bool check_logged_in(const std::string &account);
    bool check_user_name(const std::string &user_name);
    bool check_password(const std::string &user_name, const std::string &passward);
    std::string get_dir_list(const std::string &path_name);

    inline void set_user(const std::string &user) { user_ = user; }
    inline void set_current_dir(const std::string &dir) { current_dir_ = dir; }
    inline void set_connect_ip(const std::string &ip) { data_connect_ip_ = ip; }
    inline void set_connect_port(uint port) { data_connect_port_ = port; }
    inline void set_status(bool status) { status_ = status; }

    inline const std::string &user() const { return user_; }
    inline const std::string &current_dir() const { return current_dir_; }
    inline const std::string &connect_ip() const { return data_connect_ip_; }
    inline const uint connect_port() const { return data_connect_port_; }
    inline const bool status() const { return status_; }

private:

struct Server_Info {
    std::map<std::string, std::string> account_password_map; //已自带的账号和密码
    std::list<std::string> logged_account;                   //已登录的用户

    Server_Info() {
        account_password_map = {
            {"scutech",     "dingjia"},
            {"xiaoming",    "123456"},
            {"xiaobai",     "12456"},
            {"xiaohei",     "78906"},
            // {"anonymous",   ""}
        };
    }
};
    static Server_Info server_info_;
    std::string user_;
    std::string current_dir_;
    std::string data_connect_ip_;
    uint data_connect_port_;
    bool status_;
};