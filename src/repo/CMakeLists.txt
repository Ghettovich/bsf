cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

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
target_sources(repo PUBLIC
        actionarduinorepo.cpp
        arduinorepo.cpp
        iodevicerepo.cpp
        logrepo.cpp
        reciperepo.cpp
        statecoderepo.cpp
        ${HEADER_LIST})

