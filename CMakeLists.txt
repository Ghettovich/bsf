cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Bsf VERSION 1.0
            DESCRIPTION "Basalt Factory App"
            LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#add_library(bsflib OBJECT)

# LINK GLOBALLY
#
#target_link_libraries(BsfApp PUBLIC
#        Qt5::Core
#        Qt5::Gui
#        Qt5::Widgets
#        Qt5::Network
#        Qt5::Sql)

add_subdirectory(src)

add_subdirectory(test)
#
#add_subdirectory(test/server)
#
#enable_testing(true)

endif()