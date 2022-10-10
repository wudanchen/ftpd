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

const char msg_common_success[]         =                         "200 Command okay\r\n";
const char msg_pasv_success[]           =                         "227 Entering Passive Mode. (%s)\r\n";

//已使用
const char msg_cmd_not_implemented[]    =                         "202 COmmand not implemented, superfluous at this site.\r\n";
const char msg_new_user[]               =                         "220 Service ready for new user\r\n";
const char msg_user_require_pass[]      =                         "331 User name okay, need password\r\n";
const char msg_login_fail[]             =                         "430 Invalid username or password\r\n";
const char msg_login_success[]          =                         "230 User logged in, proceed\r\n";    
const char msg_pwd_success[]            =                         "257 \"%s\" is your working directory\r\n";
const char msg_action_not_taken[]       =                         "550 Requested action not taken.\r\n";
const char msg_file_success[]           =                         "250 Requested file action okay, completed\r\n";
const char msg_syntax_error[]           =                         "501 Syntax error in parameters or arguments.\r\n";// (参数语法错误)