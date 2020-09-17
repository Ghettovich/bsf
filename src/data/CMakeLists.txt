cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

# HEADER LIST
set(HEADER_LIST
        bsfdatabaseconfig.h
        )

# TARGET MAIN LIB
target_sources(bsflib
        PRIVATE
        bsfdatabaseconfig.cpp
        ${HEADER_LIST})

# TARGET BSF LIB AND INCLUDE
target_include_directories(bsflib PUBLIC ${CMAKE_CURRENT_LIST_DIR})