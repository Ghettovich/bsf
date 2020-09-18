cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# HEADER LIST
set(HEADER_LIST
        events/recipedata.h
        events/recipeinfo.h
        bsfpavementmachine.h
        datatypes.h
        fault.h
        pavementstateobject.h
        statemachine.h)

# TARGET SOURCES
target_sources(statemachine PUBLIC
        events/recipeinfo.cpp
        events/recipedata.cpp
        bsfpavementmachine.cpp
        fault.cpp
        pavementstateobject.cpp
        statemachine.cpp
        ${HEADER_LIST})
