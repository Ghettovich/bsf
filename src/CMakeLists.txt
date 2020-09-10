cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(BsfDebug)
set(CMAKE_CXX_STANDARD 14)

# DEFAULT DEBUG
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ADDITIONAL PATHS TO  BE SEARCH FOR UI FILES
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui/**/*.ui)

# DEFINE GLOBAL TARGET FOR MOC
#set(CMAKE_GLOBAL_AUTOGEN_TARGET BsfDebug)
set(CMAKE_GLOBAL_AUTOGEN_TARGET_NAME BsfMoc)


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

set(BsfDomain
        domain/action.cpp
        domain/action.h
        domain/arduino.cpp
        domain/arduino.h
        domain/bafalog.cpp
        domain/bafalog.h
        domain/detectionsensor.cpp
        domain/detectionsensor.h
        domain/iodevice.cpp
        domain/iodevice.h
        domain/iodevicetype.cpp
        domain/iodevicetype.h
        domain/recipe.cpp
        domain/recipe.h
        domain/relay.cpp
        domain/relay.h
        domain/statecode.cpp
        domain/statecode.h
        domain/transformpayload.cpp
        domain/transformpayload.h
        domain/weightcensor.cpp
        domain/weightcensor.h
        # DTO
        dto/arduinodto.cpp
        dto/arduinodto.h
        dto/iodevicedto.cpp
        dto/iodevicedto.h)

set(BsfFactory
        factory/iodeviceformfactory.cpp
        factory/iodeviceformfactory.h)

set(BsfUi
        # CONTROLLER
        controller/tab/tabcontroller.h
        controller/tab/tabcontroller.cpp
        # UI FILES -- MAIN
        ui/main/mainwindow.ui
        ui/main/mainwindow.h
        ui/main/mainwindow.cpp
        # TABS
        ui/tabs/arduinotab.h
        ui/tabs/arduinotab.cpp
        ui/tabs/iodevicetab.h
        ui/tabs/iodevicetab.cpp
        ui/tabs/logtab.cpp
        ui/tabs/logtab.h
        ui/tabs/recipetab.cpp
        ui/tabs/recipetab.h
        ui/tabs/statemachinetab.cpp
        ui/tabs/statemachinetab.h
        # TABWIDGET
        ui/tabwidget/statemachinetabwidget.cpp
        ui/tabwidget/statemachinetabwidget.h
        # FORMS
        ui/forms/detectionsensorform.ui
        ui/forms/detectionsensorform.h
        ui/forms/detectionsensorform.cpp
        ui/forms/deviceactionform.ui
        ui/forms/deviceactionform.h
        ui/forms/deviceactionform.cpp
        ui/forms/deviceform.ui
        ui/forms/deviceform.h
        ui/forms/deviceform.cpp
        ui/forms/iodeviceform.ui
        ui/forms/iodeviceform.h
        ui/forms/iodeviceform.cpp
        ui/forms/relayform.ui
        ui/forms/relayform.h
        ui/forms/relayform.cpp
        ui/forms/weightsensorform.ui
        ui/forms/weightsensorform.h
        ui/forms/weightsensorform.cpp)

set(BsfUiStateWidgets
        ui/statewidgets/selectrecipe.cpp
        ui/statewidgets/selectrecipe.h
        ui/statewidgets/statemachinepage.cpp
        ui/statewidgets/statemachinepage.h
        ui/statewidgets/weightrecipe.cpp
        ui/statewidgets/weightrecipe.h)

set(BsfDatabase
        data/bsfdatabaseconfig.cpp
        data/bsfdatabaseconfig.h
        repo/actionarduinorepo.cpp
        repo/actionarduinorepo.h
        repo/arduinorepo.cpp
        repo/arduinorepo.h
        repo/iodevicerepo.cpp
        repo/iodevicerepo.h
        repo/logrepo.cpp
        repo/logrepo.h
        repo/reciperepo.cpp
        repo/reciperepo.h
        repo/statecoderepo.cpp
        repo/statecoderepo.h)

set(BsfStatemachine
        statemachine/events/recipedata.cpp
        statemachine/events/recipedata.h
        statemachine/events/recipeinfo.cpp
        statemachine/events/recipeinfo.h
        statemachine/bsfpavementmachine.cpp
        statemachine/bsfpavementmachine.h
        statemachine/datatypes.h
        statemachine/fault.cpp
        statemachine/fault.h
        statemachine/pavementstateobject.cpp
        statemachine/pavementstateobject.h
        statemachine/statemachine.cpp
        statemachine/statemachine.h)

set(BsfService
        service/iodeviceservice.cpp
        service/iodeviceservice.h
        service/logservice.cpp
        service/logservice.h
        service/networkservice.cpp
        service/networkservice.h
        service/payloadservice.cpp
        service/payloadservice.h)

#add_library(BsfLogServiceLib SHARED
#        domain/bafalog.cpp
#        domain/bafalog.h
#        service/logservice.cpp
#        service/logservice.h)
#
#install(TARGETS BsfLogServiceLib DESTINATION lib)
#install(FILES ${BsfLogServiceLib} DESTINATION include)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Network Sql Svg REQUIRED)
# find sql lite

if (Qt5Widgets_FOUND)

    # EXEQTABLE
    add_executable(BsfDebug
            ui/main/main.cpp
            ${BsfDomain}
            ${BsfFactory}
            ${BsfUi}
            ${BsfDatabase}
            ${BsfService}
            ${BsfStatemachine}
            ${BsfUiStateWidgets}
            resource/theme.qrc)

    target_include_directories(BsfDebug PUBLIC
            Qt5Widgets_INCLUDE_DIRS
            BsfMoc)

#    target_link_libraries(BsfLogServiceLib
#            PUBLIC
#            Qt5::Core
#            Qt5::Gui
#            Qt5::Widgets
#            Qt5::Sql)

    target_link_libraries(BsfDebug
            PUBLIC
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::Network
            Qt5::Sql
            Qt5::Svg)


    configure_file(data/bsf.db data/bsf.db COPYONLY)


else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

