#include "userinfo.h"
#include <algorithm>
#include <pwd.h>
#include <unistd.h>

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
