cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)



# HEADER LIST
set(HEADER_LIST
        tst_recipe.h)

# TARGET SOURCES
target_sources(srcTestLib
        PRIVATE
        tst_recipe.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(srcTestLib
        domain
        repo
        Qt5::Test
        Qt5::Core)

target_include_directories(srcTestLib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
