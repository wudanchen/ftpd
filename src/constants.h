/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-10-09 14:40:12
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-09 14:41:50
 * @FilePath: /ftpd/src/constants.h
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#pragma once

const char msg_pasv_success[]           =                         "227 Entering Passive Mode. (%s)\r\n";

//已使用
const char msg_cmd_not_implemented[]    =                         "202 COmmand not implemented, superfluous at this site.\r\n";
const char msg_new_user[]               =                         "220 Service ready for new user\r\n";
const char msg_user_require_pass[]      =                         "331 User name okay, need password\r\n";
const char msg_login_fail[]             =                         "430 Invalid username or password\r\n";
const char msg_login_success[]          =                         "230 User logged in, proceed\r\n";    
const char msg_pwd_success[]            =                         "257 \"%s\" is your working directory\r\n";
const char msg_action_not_taken[]       =                         "550 Requested action not taken.\r\n";
const char msg_file_success[]           =                         "250 Requested file action okay, completed\r\n"; //(请求文件动作 OK,完成)
const char msg_syntax_error[]           =                         "501 Syntax error in parameters or arguments.\r\n";// (参数语法错误)
const char msg_common_success[]         =                         "200 Command okay\r\n";
const char msg_connect_fail[]           =                         "425 Can't open data connection.\r\n"; //(不能打开数据连接)
const char msg_stansfer_start[]         =                         "125 Data connection already open; transfer starting.\r\n"; //(数据连接已打开,传输开始)
const char msg_file_okay[]              =                         "150 File status okay; about to open data connection.\r\n";// (文件状态 OK,将打开数据连接)
const char msg_connection_close[]       =                         "226 Closing data connection.\r\n"; //(关闭数据连接)请求文件动作成功(例如,文件传输或者放弃)