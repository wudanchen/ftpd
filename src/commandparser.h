#pragma once

#include <vector>
#include <functional>
#include <map>

class Command_Parser {
public:
    Command_Parser();
    ~Command_Parser() {}
    void parsing_data(const char *buf, int len);
    const char *response_data() const;

private:
    void user_handle();
    void pass_handle();
    void pwd_handle();
    void cwd_handle();
    void cdup_handle();
    void port_handle();
    void retr_handle();
    void list_handle();
    void type_handle();
    void stor_handle();
    void pasv_handle();
    void rnfr_handle();
    void rnto_handle();
    void rmd_handle();
    void dele_handle();
    void mkd_handle();
    void quit_handle();
    void cmd_not_implemented_handle();

    std::vector<char> send_buff_;
    std::vector<char> recv_buff_;
    static std::map<std::string, void (Command_Parser::*)()> command_;
};