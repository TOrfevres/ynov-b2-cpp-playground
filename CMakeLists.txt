cmake_minimum_required(VERSION 3.9)
project(Initiation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/lib/boost_1_66_0")

find_package(Boost 1.36.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions( "-DHAS_BOOST" )
endif()

add_executable(Initiation main.cpp bean/Monster.cpp bean/Monster.h bean/Player.cpp bean/Player.h Utils.cpp Utils.h)