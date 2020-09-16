cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# HEADER LIST
set(HEADER_LIST
        controller/tab/tabcontroller.h
        forms/detectionsensorform.h
        forms/deviceactionform.h
        forms/deviceform.h
        forms/iodeviceform.h
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
        tabwidget/statemachinetabwidget.h
        )

target_sources(BsfApp
        PRIVATE
            # CONTROLLER
            controller/tab/tabcontroller.cpp
            # UI FILES -- MAIN
            main/mainwindow.cpp
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
            forms/deviceactionform.cpp
            forms/deviceform.cpp
            forms/deviceform.ui
            forms/iodeviceform.cpp
            forms/relayform.cpp
            forms/weightsensorform.cpp
            # STATE WIDGETS
            statewidgets/selectrecipe.cpp
            statewidgets/statemachinepage.cpp
            statewidgets/weightrecipe.cpp
        PUBLIC
            ${HEADER_LIST}
        )
