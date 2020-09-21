cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

# HEADER LIST
set(HEADER_LIST
        requestmanager/requestmanager.h
        socketmanager/socketmanager.h
        iodeviceservice.h
        logservice.h
        networkservice.h
        payloadservice.h
        )

# TARGET SOURCES
target_sources(bsflib PRIVATE
        requestmanager/requestmanager.cpp
        socketmanager/socketmanager.cpp
        iodeviceservice.cpp
        logservice.cpp
        networkservice.cpp
        payloadservice.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(bsflib
        Qt5::Core
        Qt5::Widgets
        Qt5::Network)

target_include_directories(bsflib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/service
        $<INSTALL_INTERFACE:service>)  # <prefix>/include/mylib
