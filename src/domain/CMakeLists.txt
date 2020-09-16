cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core)


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


target_sources(BsfApp
        PUBLIC
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
        PUBLIC
            ${HEADER_LIST}
        )
