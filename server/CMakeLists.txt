cmake_minimum_required(VERSION 3.29)
project(server C)

set(CMAKE_C_STANDARD 11)

add_executable(server src/main.c
        src/proxy.c
        src/utils.c
        include/proxy.h
        include/utils.h
        include/constants.h)
