cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADER_LIST
        actionarduinorepo.h
        arduinorepo.h
        iodevicerepo.h
        logrepo.h
        reciperepo.h
        statecoderepo.h
        )


target_sources(BsfApp
        PRIVATE
            actionarduinorepo.cpp
            arduinorepo.cpp
            iodevicerepo.cpp
            logrepo.cpp
            reciperepo.cpp
            statecoderepo.cpp
        PUBLIC
            ${HEADER_LIST})
