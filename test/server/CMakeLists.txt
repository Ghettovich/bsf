cmake_minimum_required(VERSION 3.7...3.18)

project(HttpServer)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

link_directories(${CMAKE_PREFIX_PATH}/usr/local/lib)



find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Network Widgets REQUIRED)

set(BsfRequestManager
        requestmanager.cpp
        requestmanager.h)


add_executable(httpserver httpserver.cpp
        httpserver.cpp
        ${BsfRequestManager})

target_link_libraries(httpserver PUBLIC
        httpmockserver
        gmock
        gtest
        microhttpd
        Qt5::Core
        Qt5::Network
        Qt5::Test
        Qt5::Widgets
        )
