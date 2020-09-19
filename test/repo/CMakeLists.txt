cmake_minimum_required(VERSION 3.7...3.18)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        actionarduinorepotest.h
        arduinorepotest.h
        iodevicerepotest.h
        reciperepotest.h
        statecoderepotest.h)

# TARGET SOURCES
target_sources(srcTestLib
        PRIVATE
        actionarduinorepotest.cpp
        arduinorepotest.cpp
        iodevicerepotest.cpp
        reciperepotest.cpp
        statecoderepotest.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(srcTestLib
        Qt5::Test
        Qt5::Core)

target_include_directories(srcTestLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/repo
        $<INSTALL_INTERFACE:repo>)  # <prefix>/include/mylib
