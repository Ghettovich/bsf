cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(bsflib SHARED "")

    # ADD SOURCES TO BSF LIB
    add_subdirectory(data)
    add_subdirectory(domain)
    add_subdirectory(parser)
    add_subdirectory(repo)
    add_subdirectory(service)
    add_subdirectory(statemachine)
    add_subdirectory(ui)

    install(TARGETS bsflib
            EXPORT bsflibTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    install(TARGETS bsflib DESTINATION include)

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/bsfConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/bsfConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/bsfConfigVersion.cmake"
            DESTINATION lib/cmake
            )

    # set version
    set(version 1.0)

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/bsfConfigVersion.cmake"
            VERSION "${version}"
            COMPATIBILITY AnyNewerVersion
    )


    export(EXPORT bsflibTargets
            FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/bsflibTargets.cmake")

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

