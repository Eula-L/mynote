cmake_minimum_required(VERSION 3.10)
project(MyThread)
 
set(CMAKE_CXX_STANDARD 11)
 
add_executable(MyThread main.cpp
        # SysInfo.cpp SysInfo.h
        HttpRequest.cpp HttpRequest.h)
