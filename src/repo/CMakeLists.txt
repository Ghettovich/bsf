cmake_minimum_required(VERSION 3.7...3.18)
project(repo)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

include_directories(${CMAKE_SOURCE_DIR}/lib)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

# HEADER LIST
set(HEADER_LIST
        actionarduinorepo.h
        arduinorepo.h
        iodevicerepo.h
        logrepo.h
        reciperepo.h
        statecoderepo.h
        )

# TARGET SOURCES
add_library(repo
        actionarduinorepo.cpp
        arduinorepo.cpp
        iodevicerepo.cpp
        logrepo.cpp
        reciperepo.cpp
        statecoderepo.cpp
        ${HEADER_LIST})

set_target_properties(repo PROPERTIES
        POSITION_INDEPENDENT_CODE False)

# Set the property version pkconfig
set_property(TARGET repo PROPERTY VERSION 1.0)

# Linkes files with QT
target_link_libraries(repo PUBLIC
        Qt5::Core
        Qt5::Sql)

target_include_directories(repo
        PUBLIC
        "$<TARGET_PROPERTY:data,INCLUDE_DIRECTORIES>"
        "$<TARGET_PROPERTY:domain,INCLUDE_DIRECTORIES>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include/repo>")

install(TARGETS repo
        EXPORT "repoTargets"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

# install header file
install(FILES ${HEADER_FILES} DESTINATION include)

install(EXPORT repoTargets
        FILE repoTargets.cmake
        NAMESPACE repo::
        DESTINATION lib/cmake
        )

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
        DESTINATION lib/cmake)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/repoConfigVersion.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT repoTargets
        FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/bsf_build/repo/repoTargets.cmake")

target_link_libraries(bsflib PUBLIC
        repo)
