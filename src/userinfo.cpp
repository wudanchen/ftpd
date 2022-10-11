/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-11 14:35:33
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-11 17:56:13
 * @FilePath: /ftpd/src/userinfo.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include "userinfo.h"

#include <algorithm>
#include <pwd.h>
#include <unistd.h>
#include <ace/Log_Msg.h>
#include <dirent.h>
#include <stdlib.h>
#include <grp.h>
#include <sys/stat.h>
#include <cstring>
#include <stdio.h>


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

void mode_to_letters(mode_t mode, char *buf)
{
    memset (buf, '-', 10);
    switch (mode & S_IFMT) {
        case S_IFBLK:   buf[0] = 'b'; break; // block device
        case S_IFCHR:   buf[0] = 'c'; break; // character device
        case S_IFDIR:   buf[0] = 'd'; break; // directory
        case S_IFIFO:   buf[0] = 'f'; break; // FIFO
        case S_IFLNK:   buf[0] = 'l'; break; // symbolic link
        case S_IFSOCK:  buf[0] = 's'; break; // socket
        default:        buf[0] = '-'; break;
    }                                                                               
    if(mode&S_IRUSR)    buf[1] = 'r';
    if(mode&S_IWUSR)    buf[2] = 'w';
    if(mode&S_IXUSR)    buf[3] = 'x';
    if(mode&S_IRGRP)    buf[4] = 'r';
    if(mode&S_IWGRP)    buf[5] = 'w';
    if(mode&S_IXGRP)    buf[6] = 'x';
    if(mode&S_IROTH)    buf[7] = 'r';
    if(mode&S_IWOTH)    buf[8] = 'w';
    if(mode&S_IXOTH)    buf[9] = 'x';
}

void uid_to_name(uid_t uid, char *buf, int len)
{
    struct passwd *pw_ptr;
    if ( (pw_ptr = getpwuid (uid)) == nullptr) {
        std::string uid_str = std::to_string(uid);
        strncpy(buf, uid_str.c_str (), len);
    }else {
        strncpy (buf, pw_ptr->pw_name, len);
    }
}

void gid_to_name (gid_t gid, char *buf, int len)
{
    struct group *grp_ptr;
    if ( (grp_ptr = getgrgid (gid)) == nullptr) {
        std::string gid_str = std::to_string (gid);
        strncpy (buf, gid_str.c_str (), len);
    }else {
        strncpy (buf, grp_ptr->gr_name, len);
    }
}

std::string User_Info::get_dir_list(const std::string &path_name)
{
    std::string msg("");
    std::string path = path_name.empty() ? current_dir_ : 
                       absolute_path(path_name) ? path_name : current_dir_ + path_name;
    DIR *dir = opendir(path.c_str());
    if(!dir) {
        return msg;
    }
    struct dirent *content;
    struct stat content_stat;
    while ((content = readdir(dir)) != nullptr) {
        char buffer[1024] = {0};
        std::string content_path = path + std::string(content->d_name);
        stat(content_path.c_str(), &content_stat);
        char mode[100] = {0}, owner[100] = {0}, group[100] = {0};
        mode_to_letters(content_stat.st_mode, mode);
        uid_to_name(content_stat.st_uid, owner, sizeof(owner));
        gid_to_name(content_stat.st_gid, group, sizeof(group));
        snprintf(buffer, sizeof(buffer), "%s %4d %-8s %-8s %8d %.12s %s \r\n",
                mode, (int)content_stat.st_nlink, owner, group, (int)content_stat.st_size,
                4+ctime(&content_stat.st_mtime), content->d_name);
        msg += std::string(buffer);
    }
    closedir(dir);
    return msg;
}

void User_Info::update_current_dir(const std::string &path_name)
{
    current_dir_ = absolute_path(path_name) ? path_name : current_dir_ + "/" + path_name;
}

bool User_Info::absolute_path(const std::string &path)
{
    bool res = path.front() == '/' ? true : false;
    return res;
}