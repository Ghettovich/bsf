cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

add_library(httpServerLib "")

add_subdirectory(server)

# HEADER LIST
set(HEADER_LIST
        requestmanager/tst_requestmanager.h
        tst_iodeviceservice.h
        tst_networkservice.h)

# TARGET SOURCES
target_sources(srcTestLib
        PRIVATE
        requestmanager/tst_requestmanager.cpp
        tst_iodeviceservice.cpp
        tst_networkservice.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(srcTestLib
        bsflib
        httpServerLib
        Qt5::Test
        Qt5::Core
        Qt5::Network)

target_include_directories(srcTestLib
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
