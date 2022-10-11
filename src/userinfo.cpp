#include "userinfo.h"

#include <algorithm>
#include <pwd.h>
#include <unistd.h>
#include <ace/Log_Msg.h>

User_Info::Server_Info User_Info::server_info_;

User_Info::User_Info()
: user_("")
, current_dir_("")
, data_connect_ip_("")
, data_connect_port_(20)
, status_(false)
{
    passwd *pwd = getpwnam(getlogin());
    current_dir_ = pwd == nullptr ? "" : pwd->pw_dir;
}

User_Info::~User_Info()
{

}

bool User_Info::check_logged_in(const std::string &account)
{
    auto it = std::find(server_info_.logged_account.begin(), server_info_.logged_account.end(), account);
    if(it == server_info_.logged_account.end()) {
        return false;
    }
    return true;
}

bool User_Info::check_user_name(const std::string &user_name)
{
    auto it = server_info_.account_password_map.find(user_name);
    if(it == server_info_.account_password_map.end()) {
        return false;
    }
    return true;
}

bool User_Info::check_password(const std::string &user_name, const std::string &password)
{
    auto it = server_info_.account_password_map.find(user_name);
    if(it == server_info_.account_password_map.end()) {
        return false;
    }
    if(it->second == password) {
        server_info_.logged_account.push_back(user_name);
        return true;
    }
    return false;
}

std::string User_Info::get_dir_list(const std::string &path_name)
{
    std::string path = path_name.empty() ? current_dir_ : (current_dir_ + "/" + path_name);
    std::string msg = "drwxrwxr-x 9 scutech scutech 4096 10月 10 19:01 . \r\n"
                      "drwxrwxr-x 8 scutech scutech 4096 10月  8 15:58 .. \r\n"
                      "drwxrwxr-x 4 scutech scutech 4096 10月 11 15:58 build \r\n"
                      "-rw-rw-r-- 1 scutech scutech  124 10月  8 10:26 CMakeL \r\n"
                      "drwxrwxr-x 2 scutech scutech 4096 10月  8 10:26 doc \r\n"
                      "drwxrwxr-x 8 scutech scutech 4096 10月 11 16:44 .git \r\n"
                      "-rw-rw-r-- 1 scutech scutech   20 9月  28 13:29 README.md \r\n"
                      "drwxrwxr-x 3 scutech scutech 4096 10月  8 10:28 release \r\n"
                      "drwxrwxr-x 2 scutech scutech 4096 10月 11 15:23 src \r\n"
                      "drwxrwxr-x 2 scutech scutech 4096 10月 11 09:28 test \r\n"
                      "drwxrwxr-x 2 scutech scutech 4096 10月 10 09:26 .vscode \r\n";
    return msg;
}