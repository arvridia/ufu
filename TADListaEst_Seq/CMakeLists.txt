cmake_minimum_required(VERSION 3.16)
project(TADListaEst_Seq C)

set(CMAKE_C_STANDARD 99)

add_executable(TADListaEst_Seq user.c listaEst_Seq.c listaEst_Seq.h cmake-build-debug/listaEst_Seq.c cmake-build-debug/listaEst_Seq.h)