cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# HEADER LIST
set(HEADER_LIST
        iodeviceformfactory.h)

# TARGET SOURCES
target_sources(bsflib
        PRIVATE
        iodeviceformfactory.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(bsflib
        Qt5::Core
        Qt5::Widgets)

target_include_directories(bsflib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/factory
        $<INSTALL_INTERFACE:factory>)  # <prefix>/include/mylib
