cmake_minimum_required(VERSION 3.16)
project(TADesferaDef C)

set(CMAKE_C_STANDARD 99)

add_executable(TADesferaDef main.c cmake-build-debug/TADpontoDef.cpp cmake-build-debug/TADpontoDef.h cmake-build-debug/TADesferaDef.cpp cmake-build-debug/TADesferaDef.h cmake-build-debug/TADpontoDef.c)