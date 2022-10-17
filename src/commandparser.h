/// \file commandparser.h
/// \brief Parse the received command
/// \author wudancheng
#pragma once
#include "userinfo.h"
#include "transmitter.h"

#include <vector>
#include <functional>
#include <map>

class Command_Parser {
public:
    typedef std::map<std::string, void (Command_Parser::*)(const std::vector<std::string> &)> Command_Handle;

    Command_Parser();
    ~Command_Parser() {}

    /// \brief farsing ftp cmmmand.
    /// \param[in] buf revice data
    /// \param[in] len data len
    
    void parsing_data(const char *buf, int len);
    /// \brief response reply
    /// \return const char* string code
    const char *response_data() const;
    
    /// \brief Set the send callback
    /// \param[] callback 
    void set_callback(const std::function<void(const std::string &)> &callback);

private:
    void user_handle(const std::vector<std::string> &recv_buffer);
    void pass_handle(const std::vector<std::string> &recv_buffer);
    void pwd_handle(const std::vector<std::string> &recv_buffer);
    void cwd_handle(const std::vector<std::string> &recv_buffer);
    void cdup_handle(const std::vector<std::string> &recv_buffer);
    void port_handle(const std::vector<std::string> &recv_buffer);
    void retr_handle(const std::vector<std::string> &recv_buffer);
    void list_handle(const std::vector<std::string> &recv_buffer);
    void stor_handle(const std::vector<std::string> &recv_buffer);
    void pasv_handle(const std::vector<std::string> &recv_buffer);
    void quit_handle(const std::vector<std::string> &recv_buffer);
    void cmd_not_implemented_handle();
    void recv_buffer_handle(const char *buff, std::vector<std::string> &recv_buffer);
    void send_buffer_handle(const std::string &msg, bool send_immediately = false);
    std::vector<std::string> spilt(const std::string &str, const char separator);

    std::string send_buff_;
    User_Info info_;
    std::function<void(const std::string &)> output_signal_callback_;
    Transmitter transmitter_;
    static Command_Handle command_;
};
