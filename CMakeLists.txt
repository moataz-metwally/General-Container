cmake_minimum_required(VERSION 3.10)

project(General_Container)


add_executable(main src/main.cpp)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=c++17 -fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2  -Wl,-z,relro -Wconversion -Wsign-conversion -Wformat-security -Werror -pie -fPIE")

target_include_directories(main PUBLIC inc/)
