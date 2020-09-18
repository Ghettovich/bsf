cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

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
        weightcensor.h)

# TARGET SOURCES
target_sources(bsflib PRIVATE
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
        ${HEADER_LIST})

target_link_libraries(bsflib
        Qt5::Core)

target_include_directories(bsflib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/domain
        $<INSTALL_INTERFACE:domain>  # <prefix>/include/mylib
        )

