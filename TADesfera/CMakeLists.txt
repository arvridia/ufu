cmake_minimum_required(VERSION 3.16)
project(TADesfera C)

set(CMAKE_C_STANDARD 99)

add_executable(TADesfera user.c TADesfera.c TADesfera.h cmake-build-debug/TADponto.c cmake-build-debug/TADponto.h)