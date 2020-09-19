cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Bsf VERSION 1.0
            DESCRIPTION "Basalt Factory App")


# BUILD OPTION
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(src "")

# Add src directory
add_subdirectory(src)
add_subdirectory(apps)
#add_subdirectory(test)

#
#add_subdirectory(test/server)
#
#enable_testing(true)
