cmake_minimum_required(VERSION 3.14)
project(doudizhu)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.c function.c function.h struct.h)

add_executable(untitled ${SOURCE_FILES})