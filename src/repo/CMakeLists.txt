cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

# HEADER LIST
set(HEADER_LIST
        actionarduinorepo.h
        arduinorepo.h
        iodevicerepo.h
        logrepo.h
        reciperepo.h
        statecoderepo.h
        )

# TARGET SOURCES
target_sources(bsflib PRIVATE
        actionarduinorepo.cpp
        arduinorepo.cpp
        iodevicerepo.cpp
        logrepo.cpp
        reciperepo.cpp
        statecoderepo.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(bsflib
        Qt5::Core
        Qt5::Sql)

target_include_directories(bsflib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/repo>")
