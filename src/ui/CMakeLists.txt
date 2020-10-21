cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

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
target_sources(bsflib PRIVATE
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
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(bsflib
        Qt5::Core
        Qt5::Widgets)

target_include_directories(bsflib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/ui>")
