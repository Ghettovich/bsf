cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

# HEADER LIST
set(HEADER_LIST
        requestmanager/requestmanager.h
        socketmanager/tcpserver.h
        socketmanager/socketclient.h
        iodeviceservice.h
        logservice.h
        networkservice.h
        )

# TARGET SOURCES
add_library(service MODULE
        requestmanager/requestmanager.cpp
        socketmanager/tcpserver.cpp
        socketmanager/socketclient.cpp
        iodeviceservice.cpp
        logservice.cpp
        networkservice.cpp
        ${HEADER_LIST})

target_link_libraries(service
        Qt5::Core
        Qt5::Widgets
        Qt5::Network)

target_include_directories(service
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/service>"
        "$<INSTALL_INTERFACE:include/service>")

install(TARGETS service
        EXPORT serviceTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(FILES ${HEADER_LIST} DESTINATION include/service)

install(EXPORT serviceTargets
        FILE serviceTargets.cmake
        DESTINATION lib/cmake
        )

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/serviceTargets.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/serviceTargets.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/serviceTargets.cmake"
        DESTINATION lib/cmake)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/serviceTargets.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT serviceTargets
        FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/serviceTargets.cmake")