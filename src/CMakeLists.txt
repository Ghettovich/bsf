cmake_minimum_required(VERSION 3.7...3.18)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(bsflib SHARED "")

    # ADD SOURCES TO BSF LIB
    add_subdirectory(data)
    add_subdirectory(domain)
    add_subdirectory(factory)
    add_subdirectory(parser)
    add_subdirectory(repo)
    add_subdirectory(service)
    add_subdirectory(statemachine)
    add_subdirectory(ui)

    install(TARGETS bsflib DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

    add_custom_command(
            TARGET bsflib POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:bsflib>
            ${CMAKE_PREFIX_PATH}/usr/local/lib/bsf/$<TARGET_FILE_NAME:bsflib>)

#    target_sources(src
#            PUBLIC
#            $<TARGET_OBJECTS:bsflib>
#            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

