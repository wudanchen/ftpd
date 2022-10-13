cmake_minimum_required(VERSION 3.0.0)
project(FTPD)

add_subdirectory(src bin)
add_subdirectory(test gtest)
set(RELEASE_DIR ${PROJECT_SOURCE_DIR}/release)
