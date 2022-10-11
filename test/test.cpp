/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-11 14:56:10
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-11 17:37:44
 * @FilePath: /ftpd/test/test.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include <iostream>
#include <vector>

#include <pwd.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <cstring>
#include <string>

#include <grp.h>

// using namespace std;

// void recv_buffer_handle(const char *buff, std::vector<std::string> &recv_buffer)
// {
//     char *recv_buff = (char *)buff;
//     auto *pre_it = recv_buff;
//     for(auto *it = recv_buff; *it != '\0'; ++it) {
//         if(*it == ' ') {
//             recv_buffer.push_back(std::string(pre_it, it));
//             pre_it = it + 1;
//         }else if(*it == '\r' || *it == '\n') {
//             if(pre_it != it) {
//                 recv_buffer.push_back(std::string(pre_it, it));
//             }
//             break;
//         }
//     }
// }

// void mode_to_letters(mode_t mode, char *buf)
// {
//     memset (buf, '-', 10);
//     switch (mode & S_IFMT) 
//     {
//         case S_IFBLK:   buf[0] = 'b'; break; // block device
//         case S_IFCHR:   buf[0] = 'c'; break; // character device
//         case S_IFDIR:   buf[0] = 'd'; break; // directory
//         case S_IFIFO:   buf[0] = 'f'; break; // FIFO
//         case S_IFLNK:   buf[0] = 'l'; break; // symbolic link
//         case S_IFSOCK:  buf[0] = 's'; break; // socket
//         default:        buf[0] = '-'; break;
//     }
                                                                                               
//     if(mode&S_IRUSR)    buf[1] = 'r';
//     if(mode&S_IWUSR)    buf[2] = 'w';
//     if(mode&S_IXUSR)    buf[3] = 'x';
//     if(mode&S_IRGRP)    buf[4] = 'r';
//     if(mode&S_IWGRP)    buf[5] = 'w';
//     if(mode&S_IXGRP)    buf[6] = 'x';
//     if(mode&S_IROTH)    buf[7] = 'r';
//     if(mode&S_IWOTH)    buf[8] = 'w';
//     if(mode&S_IXOTH)    buf[9] = 'x';
// }

// void uid_to_name (uid_t uid, char *buf)
// {
//     struct passwd *pw_ptr;
//     if ( (pw_ptr = getpwuid (uid)) == NULL)
//     {
//         std::string uid_str = std::to_string (uid);
//         strncpy (buf, uid_str.c_str (), 8);
//     }
//     else
//         strncpy (buf, pw_ptr->pw_name, 8);
// }

// void gid_to_name (gid_t gid, char *buf)
// {
//     struct group *grp_ptr;
//     if ( (grp_ptr = getgrgid (gid)) == NULL)
//     {
//         std::string gid_str = std::to_string (gid);
//         strncpy (buf, gid_str.c_str (), 8);
//     }
//     else
//         strncpy (buf, grp_ptr->gr_name, 8);
// }

// int list_dir (const std::string &dir_path)
// {
//     std::string path = dir_path;
//     DIR *dir = opendir (path.c_str ());
    
//     struct dirent *content;
//     struct stat content_stat;
//     while ( (content = readdir (dir)) != NULL)
//     {

//         char data_buffer_[2048] = {0};
//         std::string content_path = path + std::string(content->d_name);
//         stat (content_path.c_str (), &content_stat);

//         char mode[100] = {0};
//         mode_to_letters (content_stat.st_mode, mode);

//         char owner[100] = {0};
//         uid_to_name (content_stat.st_uid, owner);

//         char group[100]= {0};
//         gid_to_name (content_stat.st_gid, group);

//         int n = snprintf(data_buffer_,2048,"%s %4d %-8s %-8s %8d %.12s ",
//                         mode,
//                         (int)content_stat.st_nlink,
//                         owner,
//                         group,
//                         (int)content_stat.st_size,
//                         4+ctime(&content_stat.st_mtime));

//         int name_len = snprintf (data_buffer_ + n, 2048 - n, "%s", content->d_name);
//         data_buffer_[n + name_len] = '\r';
//         data_buffer_[n + name_len + 1] = '\n';
//         printf("%s", data_buffer_);
//     }
    
//     closedir (dir);
//     return 0;
// }

// int main() {
//     const char *path = "/home/wdc/share";
//     // DIR *dirp = opendir(path);
//     // struct dirent *dp;
//     // while ((dp = readdir(dirp)) != NULL) {
//     //     printf("innode = %d\t", dp->d_ino);
//     //     printf("reclen = %d\t", dp->d_reclen);
//     //     printf("name = %s\n", dp->d_name);
//     // }
//     // closedir(dirp);
//     list_dir(path);
//     return 0;
// }

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

std::string get_dir_list(const std::string &path_name)
{
    std::string msg("");
    DIR *dir = opendir(path_name.c_str());
    if(!dir) {
        return msg;
    }
    struct dirent *content;
    struct stat content_stat;
    while ((content = readdir(dir)) != nullptr) {
        char buffer[1024] = {0};
        std::string content_path = path_name + std::string(content->d_name);
        stat(content_path.c_str(), &content_stat);
        char mode[100] = {0}, owner[100] = {0}, group[100] = {0};
        mode_to_letters(content_stat.st_mode, mode);
        uid_to_name(content_stat.st_uid, owner, 8);
        gid_to_name(content_stat.st_gid, group, 8);
        snprintf(buffer, sizeof(buffer), "%s %4d %-8s %-8s %8d %.12s %s \r\n",
                mode, (int)content_stat.st_nlink, owner, group, (int)content_stat.st_size,
                4+ctime(&content_stat.st_mtime), content->d_name);
        
        printf("%s", buffer);
        msg += std::string(buffer);
    }
    // printf("%s", msg.c_str());
    closedir(dir);
    return msg;
}

int main() {
    get_dir_list("/home/wdc/share");
}