
#include <gtest/gtest.h>
#include "userinfo.h"

//测试密码
TEST(UserInfo, password) {
    User_Info info;
    EXPECT_TRUE(info.check_password("scutech", "dingjia"));
    EXPECT_TRUE(info.check_password("xiaobai", "12456"));
    EXPECT_FALSE(info.check_password("xiaoming", "haha"));
    EXPECT_FALSE(info.check_password("xiaohei", "hehe"));
}

