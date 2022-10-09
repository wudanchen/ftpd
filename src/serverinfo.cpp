#include "serverinfo.h"
#include <algorithm>

Server_Info::Server_Info()
{
    account_password_map_ = {
        {"scutech",     "dingjia"},
        {"xiaoming",    "123456"},
        {"xiaobai",     "12456"},
        {"xiaohei",     "78906"},
        {"anonymous",   ""}
    };
}

Server_Info::~Server_Info()
{
    
}

bool Server_Info::check_user_name(const std::string &user_name)
{
    auto it = account_password_map_.find(user_name);
    if(it == account_password_map_.end()) {
        return false;
    }
    return true;
}

bool Server_Info::check_logged_in(const std::string &account)
{
    auto it = std::find(logged_account_.begin(), logged_account_.end(), account);
    if(it == logged_account_.end()) {
        return false;
    }
    return true;
}

