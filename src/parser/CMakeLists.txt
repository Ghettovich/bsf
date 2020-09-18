cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        transformpayload.h)

# TARGET SOURCES
target_sources(bsflib
        PRIVATE
        transformpayload.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(bsflib
        Qt5::Core)

target_include_directories(bsflib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/parser
        $<INSTALL_INTERFACE:parser>  # <prefix>/include/mylib
        )

#target_include_directories(parser PRIVATE
#        ${CMAKE_BINARY_DIR})

#target_link_libraries(parser
#        Qt5::Core
#        Qt5::Widgets)
#
#install(TARGETS parser DESTINATION lib)
#install(FILES ${HEADER_LIST} DESTINATION include)