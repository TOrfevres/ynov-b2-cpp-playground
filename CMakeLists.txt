cmake_minimum_required(VERSION 3.9)
project(Initiation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Initiation main.cpp bean/Monster.cpp bean/Monster.h bean/Player.cpp bean/Player.h)