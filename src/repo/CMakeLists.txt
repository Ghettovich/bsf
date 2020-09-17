cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


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
target_sources(bsflib
        PRIVATE
            actionarduinorepo.cpp
            arduinorepo.cpp
            iodevicerepo.cpp
            logrepo.cpp
            reciperepo.cpp
            statecoderepo.cpp
            ${HEADER_LIST})

# TARGET BSF LIB AND INCLUDE
target_include_directories(bsflib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
