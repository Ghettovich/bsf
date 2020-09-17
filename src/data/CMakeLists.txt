cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)


set(HEADER_LIST
        bsfdatabaseconfig.h)

target_sources(bsflib
        PRIVATE
            bsfdatabaseconfig.cpp
        PUBLIC
            ${HEADER_LIST})
