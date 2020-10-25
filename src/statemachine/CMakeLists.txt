cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

include_directories(${CMAKE_SOURCE_DIR}/lib)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        events/recipedata.h
        events/recipeinfo.h
        bsfpavementmachine.h
        datatypes.h
        fault.h
        pavementstateobject.h
        statemachine.h)

# TARGET SOURCES
add_library(statemachine
        events/recipeinfo.cpp
        events/recipedata.cpp
        bsfpavementmachine.cpp
        fault.cpp
        pavementstateobject.cpp
        statemachine.cpp
        ${HEADER_LIST})

# TARGET
target_link_libraries(statemachine PUBLIC
        Qt5::Core)

target_include_directories(statemachine
        PUBLIC
        "$<TARGET_PROPERTY:domain,INCLUDE_DIRECTORIES>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include/statemachine>")

install(TARGETS statemachine
        EXPORT statemachineTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

# install header file
install(FILES ${HEADER_FILES} DESTINATION include)

install(EXPORT statemachineTargets
        FILE statemachineTargets.cmake
        NAMESPACE statemachine::
        DESTINATION lib/cmake
        )

install(TARGETS statemachine DESTINATION lib EXPORT bsflib)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/statemachineTargets.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/statemachineTargets.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/statemachineTargetsVersion.cmake"
        DESTINATION lib/cmake)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/statemachineTargetsVersion.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT statemachineTargets
        FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/statemachineTargets.cmake")

target_link_libraries(bsflib PUBLIC
        statemachine)
