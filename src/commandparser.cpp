#include "commandparser.h"
#include "constants.h"

#include <ace/Log_Msg.h>
#include <cstring>
#include <algorithm>

std::map<std::string, void (Command_Parser::*)()> Command_Parser::command_ =
{
    { "USER", &Command_Parser::user_handle },
    { "PASS", &Command_Parser::pass_handle },
    { "QUIT", &Command_Parser::quit_handle },
    { "PWD", &Command_Parser::pwd_handle },
    { "CWD", &Command_Parser::cwd_handle },
    { "CDUP", &Command_Parser::cdup_handle },
    { "PORT", &Command_Parser::port_handle },
    { "RETR", &Command_Parser::retr_handle },
    { "LIST", &Command_Parser::list_handle },
    { "TYPE", &Command_Parser::type_handle },
    { "STOR", &Command_Parser::stor_handle },
    { "PASV", &Command_Parser::pasv_handle },
    { "RNFR", &Command_Parser::rnfr_handle },
    { "RNTO", &Command_Parser::rnto_handle },
    { "RMD", &Command_Parser::rmd_handle },
    { "DELE", &Command_Parser::dele_handle },
    { "MKD", &Command_Parser::mkd_handle }
};

Command_Parser::Command_Parser()
{
}

void Command_Parser::parsing_data(const char *buf, int len)
{
    const char *space_it = strchr(buf, ' ');
    space_it = space_it == nullptr ? buf + strlen(buf) : space_it;
    std::string command_str(buf, space_it);
    ACE_DEBUG((LM_DEBUG, "command str : %s\n", command_str));
    auto it = command_.find(command_str);
    if(it != command_.end()) {
        (this->*(it->second))();
    }else {
        cmd_not_implemented_handle();
    }
}

const char *Command_Parser::response_data() const
{
    return send_buff_.data();
}

void Command_Parser::cmd_not_implemented_handle()
{
    send_buff_.clear();
    send_buff_.resize(sizeof(msg_cmd_not_implemented));
    std::copy(send_buff_.begin(), send_buff_.end(), msg_cmd_not_implemented);
}