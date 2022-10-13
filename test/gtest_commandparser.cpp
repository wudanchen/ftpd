
#include <gtest/gtest.h>
#include "commandparser.h"
#include "constants.h"

#include <iostream>

TEST(CommandParser, UserHandle) {
    Command_Parser parser;
    std::string buf = "uSeR \r\n";
    parser.parsing_data(buf.c_str(), buf.size());
    EXPECT_STREQ(msg_login_fail, parser.response_data());
    buf.assign("USER scutech\r\n");
    parser.parsing_data(buf.c_str(), buf.size());
    EXPECT_STREQ(msg_user_require_pass, parser.response_data());
}