cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

# HEADER LIST
set(HEADER_LIST
        bsfdatabaseconfig.h)

# TARGET MAIN LIB
add_library(dbconf MODULE
        bsfdatabaseconfig.cpp
        ${HEADER_LIST})

target_sources(bsflib PRIVATE ${dbconf})

# Set the property version pkconfig
set_property(TARGET dbconf PROPERTY VERSION 1.0)

# Linkes files with QT
target_link_libraries(dbconf
        Qt5::Core
        Qt5::Sql)

# Define rules for exporting domain
target_include_directories(dbconf
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/data>"
        "$<INSTALL_INTERFACE:include/data>")

install(TARGETS dbconf
        EXPORT dbconfTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(FILES ${HEADER_LIST} DESTINATION include/data)

install(EXPORT dbconfTargets
        FILE dbconfTargets.cmake
        DESTINATION lib/cmake
        )

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/dbconfTargets.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dbconfTargets.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dbconfTargetsVersion.cmake"
        DESTINATION lib/cmake
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/dbconfTargets.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT dbconfTargets
        FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/dbconfTargets.cmake")