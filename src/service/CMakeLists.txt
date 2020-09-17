cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(HEADER_LIST
        iodeviceservice.h
        logservice.h
        networkservice.h
        payloadservice.h
        )


target_sources(bsflib
        PRIVATE
            iodeviceservice.cpp
            logservice.cpp
            networkservice.cpp
            payloadservice.cpp
        PUBLIC
            ${HEADER_LIST})