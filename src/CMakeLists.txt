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

# BUILD OPTION
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Core Sql Network REQUIRED)

# ADD LIBRARY
add_library(data STATIC "")
add_library(domain STATIC "")
add_library(factory STATIC "")
add_library(parser STATIC "")
add_library(repo STATIC "")
add_library(service STATIC "")
add_library(statemachine STATIC "")
add_library(ui STATIC "")

add_subdirectory(data)
add_subdirectory(domain)
add_subdirectory(factory)
add_subdirectory(parser)
add_subdirectory(repo)
add_subdirectory(service)
add_subdirectory(statemachine)
add_subdirectory(ui)

target_link_libraries(data
        Qt5::Core
        Qt5::Sql)

target_link_libraries(domain
        Qt5::Core)

target_link_libraries(factory
        domain
        ui
        Qt5::Core
        Qt5::Widgets)

target_link_libraries(parser
        Qt5::Core)

target_link_libraries(repo
        domain
        Qt5::Core
        Qt5::Sql)

target_link_libraries(service
        parser
        domain
        ui
        repo
        Qt5::Core
        Qt5::Widgets
        Qt5::Network)

target_link_libraries(statemachine
        domain
        Qt5::Core)

target_link_libraries(ui
        domain
        statemachine
        service
        Qt5::Core
        Qt5::Widgets)






#target_include_directories(BsfApp PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if (Qt5Widgets_FOUND)

    add_executable(BsfApp ui/main/main.cpp resource/theme.qrc)
    target_link_libraries(BsfApp data domain factory parser repo service statemachine ui Qt5::Widgets)

    # All users of this library will need at least C++14
    #target_compile_features(bsflib PUBLIC cxx_std_14)

    # COPY DATABASE
    add_custom_command(
            TARGET BsfApp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/src/data/bsf.db
            ${CMAKE_BINARY_DIR}/src/data/bsf.db)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

