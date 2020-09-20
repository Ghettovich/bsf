cmake_minimum_required(VERSION 3.7...3.18)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Qt5 COMPONENTS Core)

# httpmockserver, gmock and gtest installed here
include_directories(${CMAKE_PREFIX_PATH}/usr/local/lib)

find_library(
        httpmockserverLib
        httpmockserver
)
message(${httpmockserverLib})

find_library(
        gmockLib
        gmock
)
message(${gmockLib})

find_library(
        gtestLib
        gtest
)
message(${gtestLib})

# available in usr/lib
find_library(
        microhttpdLib
        microhttpd
)
message(${microhttpdLib})

target_sources(httpServerLib
        PRIVATE
        httpserver.cpp
        PUBLIC
        httpserver.h)

target_link_libraries(httpServerLib
        ${httpmockserverLib}
        ${gmockLib}
        ${gtestLib}
        ${microhttpdLib}
        -lpthread # Taken from httpmock server test example
        Qt5::Core)

target_include_directories(httpServerLib PRIVATE
        httpmockserverLib)

install(TARGETS httpServerLib DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(HttpServer httpserver.cpp)

add_test(NAME HttpServer COMMAND HttpServer)

target_link_libraries(HttpServer
        httpServerLib
        Qt5::Core)

target_include_directories(HttpServer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server
        $<INSTALL_INTERFACE:server>)
