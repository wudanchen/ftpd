#pragma once

const char msg_connection_ready[] = "150 Data connection already open; transfer starting\r\n";
const char msg_common_success[]   = "200 Command okay\r\n";
const char msg_new_user[]         = "220 Service ready for new user\r\n";
const char msg_pasv_success[]     = "227 Entering Passive Mode. (%s)\r\n";
const char msg_login_success[]    = "230 User logged in, proceed\r\n";
const char msg_file_success[]     = "250 Requested file action okay, completed\r\n";
const char msg_cur_path[]         = "257 \"%s\" is your working directory\r\n";
