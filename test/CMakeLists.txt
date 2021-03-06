cmake_minimum_required(VERSION 3.7...3.18)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../src)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(srcTestLib SHARED "")

    add_subdirectory(domain)
    add_subdirectory(parser)
    add_subdirectory(repo)
    add_subdirectory(service)

    install(TARGETS srcTestLib DESTINATION include)

    add_executable(BsfTest
            AutoTest.cpp
            AutoTest.h)

    target_link_libraries(BsfTest PUBLIC
            bsflib
            srcTestLib
            Qt5::Test
            Qt5::Widgets)

    add_custom_command(
            TARGET BsfTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/test/resource/payload.json
            ${CMAKE_BINARY_DIR}/test/resource/payload.json)

    add_custom_command(
            TARGET BsfTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/test/resource/recipePayload.json
            ${CMAKE_BINARY_DIR}/test/resource/recipePayload.json)

    add_test(NAME BsfTest COMMAND BsfTest)
else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)



