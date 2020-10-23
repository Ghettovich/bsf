cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        transformpayload.h)

# TARGET SOURCES
add_library(parser SHARED
        transformpayload.cpp
        ${HEADER_LIST})

target_sources(bsflib PRIVATE ${parser})

# Set the property version pkconfig
set_property(TARGET dbconf PROPERTY VERSION 1.0)

# Linkes files with QT
target_link_libraries(parser
        Qt5::Core)

target_include_directories(parser
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/parser>"
        "$<INSTALL_INTERFACE:include/parser>")

install(TARGETS parser
        EXPORT parserTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(FILES ${HEADER_LIST} DESTINATION include/parser)

install(EXPORT parserTargets
        FILE parserTargets.cmake
        DESTINATION lib/cmake
        )

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/parserTargets.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/parserTargets.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/parserTargetsVersion.cmake"
        DESTINATION lib/cmake
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/parserTargets.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT parserTargets
        FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/parserTargets.cmake")