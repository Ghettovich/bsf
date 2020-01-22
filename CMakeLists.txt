cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Bsf)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(src)
