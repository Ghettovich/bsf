cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# HEADER LIST
set(HEADER_LIST
        iodeviceservice.h
        logservice.h
        networkservice.h
        payloadservice.h
        )

# TARGET SOURCES
target_sources(service PUBLIC
        iodeviceservice.cpp
        logservice.cpp
        networkservice.cpp
        payloadservice.cpp
        ${HEADER_LIST})
