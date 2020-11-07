cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

include_directories(${CMAKE_SOURCE_DIR}/lib)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

# HEADER LIST
set(HEADER_LIST
        controller/tab/tabcontroller.h
        forms/detectionsensorform.h
        forms/deviceactionform.h
        forms/deviceform.h
        forms/iodeviceform.h
        forms/mainform.h
        model/tablecomponentmodel.h
        forms/relayform.h
        forms/weightsensorform.h
        main/mainwindow.h
        statewidgets/selectrecipe.h
        statewidgets/statemachinepage.h
        statewidgets/weightrecipe.h
        tabs/arduinotab.h
        tabs/iodevicetab.h
        tabs/logtab.h
        tabs/recipetab.h
        tabs/statemachinetab.h
        tabwidget/statemachinetabwidget.h)

# TARGET SOURCES
add_library(ui
        # CONTROLLER
        controller/tab/tabcontroller.cpp
        # UI FILES -- MAIN
        main/mainwindow.cpp
        main/mainwindow.ui
        # MODELS
        model/tablecomponentmodel.cpp
        # TABS
        tabs/arduinotab.cpp
        tabs/iodevicetab.cpp
        tabs/logtab.cpp
        tabs/recipetab.cpp
        tabs/statemachinetab.cpp
        # TABWIDGET
        tabwidget/statemachinetabwidget.cpp
        # FORMS
        forms/detectionsensorform.cpp
        forms/detectionsensorform.ui
        forms/deviceactionform.cpp
        forms/deviceactionform.ui
        forms/deviceform.cpp
        forms/deviceform.ui
        forms/iodeviceform.cpp
        forms/iodeviceform.ui
        forms/mainform.cpp
        forms/relayform.cpp
        forms/relayform.ui
        forms/weightsensorform.cpp
        forms/weightsensorform.ui
        # STATE WIDGETS
        statewidgets/selectrecipe.cpp
        statewidgets/statemachinepage.cpp
        statewidgets/weightrecipe.cpp
        ${HEADER_LIST})

target_link_libraries(ui PUBLIC
        Qt5::Core
        Qt5::Widgets)

target_include_directories(ui
        PUBLIC
        "$<TARGET_PROPERTY:domain,INCLUDE_DIRECTORIES>"
        "$<TARGET_PROPERTY:repo,INCLUDE_DIRECTORIES>"
        "$<TARGET_PROPERTY:service,INCLUDE_DIRECTORIES>"
        "$<TARGET_PROPERTY:statemachine,INCLUDE_DIRECTORIES>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include/ui>")

install(TARGETS ui
        EXPORT uiTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

# install header file
install(FILES ${HEADER_FILES} DESTINATION include)

install(EXPORT uiTargets
        FILE uiTargets.cmake
        NAMESPACE ui::
        DESTINATION lib/cmake
        )

install(TARGETS ui DESTINATION lib EXPORT bsflib)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/uiConfig.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/uiConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/uiConfigVersion.cmake"
        DESTINATION lib/cmake)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/uiConfigVersion.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT uiTargets
        FILE "${CMAKE_INSTALL_PREFIX}/lib/bsf/bsf_build/ui/uiTargets.cmake")

target_link_libraries(bsflib PUBLIC
        ui)
