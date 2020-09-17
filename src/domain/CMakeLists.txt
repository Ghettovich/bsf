cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# HEADER LIST
set(HEADER_LIST
        action.h
        arduino.h
        bafalog.h
        detectionsensor.h
        iodevice.h
        iodevicetype.h
        recipe.h
        relay.h
        statecode.h
        weightcensor.h
        )

# TARGET SOURCES
target_sources(bsflib
        PRIVATE
            action.cpp
            arduino.cpp
            bafalog.cpp
            detectionsensor.cpp
            iodevice.cpp
            iodevicetype.cpp
            recipe.cpp
            relay.cpp
            statecode.cpp
            weightcensor.cpp
            ${HEADER_LIST}
        )

# TARGET BSF LIB AND INCLUDE
target_include_directories(bsflib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
