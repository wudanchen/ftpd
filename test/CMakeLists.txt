cmake_minimum_required(VERSION 3.0.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

link_libraries(ACE pthread ftp gtest_main)
include_directories(${PROJECT_SOURCE_DIR}/src)
message("path : ${PROJECT_SOURCE_DIR}")
add_executable(gtest_userinfo gtest_userinfo.cpp)
add_executable(gtest_parser gtest_commandparser.cpp)

include(GoogleTest)
gtest_discover_tests(gtest_userinfo)
gtest_discover_tests(gtest_parser)
