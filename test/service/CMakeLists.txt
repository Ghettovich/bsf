cmake_minimum_required(VERSION 3.7...3.18)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)


add_library(httpServerLib "")


add_subdirectory(server)

# HEADER LIST
set(HEADER_LIST
        requestmanager/tst_requestmanager.h
        socketmanager/tst_socketmanager.h
        socketmanager/udpserver.h
        tst_iodeviceservice.h
        tst_networkservice.h
        tst_payloadservice.h)

# TARGET SOURCES
target_sources(srcTestLib
        PRIVATE
        requestmanager/tst_requestmanager.cpp
        socketmanager/tst_socketmanager.cpp
        socketmanager/udpserver.cpp
        tst_iodeviceservice.cpp
        tst_networkservice.cpp
        tst_payloadservice.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(srcTestLib
        httpServerLib
        Qt5::Test
        Qt5::Core
        Qt5::Network)

target_include_directories(srcTestLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/service
        $<INSTALL_INTERFACE:service>)  # <prefix>/include/mylib

#add_executable(ServiceTest AutoServiceTest.cpp)
#
#target_link_libraries(ServiceTest
#        httpServerLib
#        srcTestLib
#        Qt5::Core
#        Qt5::Widgets
#        Qt5::Network
#        Qt5::Test)
