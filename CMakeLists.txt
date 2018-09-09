cmake_minimum_required(VERSION 3.12)
project(Sistemas_Operacionais)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp VirtualHD.h Manager.h)
add_executable(Sistemas_Operacionais ${SOURCE_FILES})