cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(BsfDebug)
set(CMAKE_CXX_STANDARD 14)

# DEFAULT DEBUG
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

SET(CMAKE_PREFIX_PATH "C:/Qt/5.12.6/mingw73_64;C:/Qt/Tools/mingw730_64/bin;")

# ADDITIONAL PATHS TO  BE SEARCH FOR UI FILES
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui/**/*.ui)

# DEFINE GLOBAL TARGET FOR MOC
#set(CMAKE_GLOBAL_AUTOGEN_TARGET BsfDebug)
#set(CMAKE_GLOBAL_AUTOGEN_TARGET_NAME BsfMoc)


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

set(BsfDomain
        domain/action.cpp
        domain/arduino.cpp
        #        domain/iodevice.cpp
        #        domain/iodevicetype.cpp
        domain/bafalog.cpp

        #        domain/recipe.cpp
        #        domain/statecode.cpp
        #        domain/transformpayload.cpp
        #        domain/weightcensor.cpp
        # DTO
        #        dto/arduinodto.cpp
        #        dto/iodevicedto.cpp
        )

set(BsfFactory
        #        factory/iodeviceformfactory.cpp
        )

set(BsfUi
        # UI FILES -- MAIN
        ui/main/mainwindow.ui
        ui/main/mainwindow.cpp
        # TABS
        #        ui/tabs/arduinotab.cpp
        #        ui/tabs/iodevicetab.cpp
        ui/tabs/logtab.cpp
        ui/tabs/logtab.h
        #        ui/tabs/recipetab.cpp
        #        ui/tabs/statemachinetab.cpp
        # FORMS
        #        ui/forms/detectionsensorform.ui
        #        ui/forms/detectionsensorform.cpp
        #        ui/forms/deviceactionform.ui
        #        ui/forms/deviceactionform.cpp
        #        ui/forms/deviceform.ui
        #        ui/forms/deviceform.cpp
        #        ui/forms/iodeviceform.ui
        #        ui/forms/iodeviceform.cpp
        #        ui/forms/relayform.ui
        #        ui/forms/relayform.cpp
        #        ui/forms/weightsensorform.ui
        #        ui/forms/weightsensorform.cpp
        )

set(BsfController
        controller/tab/tabcontroller.cpp
        controller/tab/tabcontroller.h
        #        controller/device/devicecontroller.cpp
        )

set(BsfDatabase
        data/bsfdatabaseconfig.cpp
        #        repo/actionarduinorepo.cpp
        #        repo/arduinorepo.cpp
        #        repo/iodevicerepo.cpp
        repo/logrepo.cpp
        #        repo/reciperepo.cpp
        #        repo/statecoderepo.cpp
        )

set(BsfStatemachine
        #        statemachine/events/recipedata.cpp
        #        statemachine/events/recipeinfo.cpp
        #        statemachine/bsfpavementmachine.cpp
        #        statemachine/fault.cpp
        #        statemachine/pavementstateobject.cpp
        #        statemachine/statemachine.cpp
        #        statemachine/statemachine.h
        )

set(BsfService
        #        service/iodeviceservice.cpp
        service/logservice.cpp
        #        service/payloadservice.cpp
        )


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Network Sql REQUIRED)
# find sql lite

if (Qt5Widgets_FOUND)

    # EXEQTABLE
    add_executable(BsfDebug
            ui/main/main.cpp
            ${BsfDomain}
            ${BsfFactory}
            ${BsfUi}
            ${BsfController}
            ${BsfDatabase}
            ${BsfService}
            ${BsfStatemachine}
            )

    target_include_directories(BsfDebug PUBLIC
            Qt5Widgets_INCLUDE_DIRS
            )

    target_link_libraries(BsfDebug
            PUBLIC
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::Network
            Qt5::Sql
            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)


#

#if(WIN32)
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Sql> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#endif(WIN32)


# add files in UI folder
#add_subdirectory(ui)

# SOURCE Controller
#set(BsfController
#        controller/devicecontroller.cpp
#        controller/tabcontroller.cpp)
#
## SOURCE DATA
#set(BsfDatabase
#        data/bsfdatabaseconfig.cpp
#        repo/actionarduinorepo.cpp
#        repo/arduinorepo.cpp
#        repo/iodevicerepo.cpp
#        repo/logrepo.cpp
#        repo/reciperepo.cpp
#        repo/statecoderepo.cpp)
#
## SOURCE domain
#set(BsfDomain
#        domain/action.cpp
#        domain/arduino.cpp
#        domain/iodevice.cpp
#        domain/log.cpp
#        domain/recipe.cpp
#        domain/transformpayload.cpp
#        domain/weightcensor.cpp)
#
## SOURCCE DTO
#set(BsfDto
#        dto/arduinodto.cpp
#        dto/iodevicedto.cpp)
#
### SOURCE service
#set(BsfService
#        service/iodeviceservice.cpp
#        service/logservice.cpp
#        service/payloadservice.cpp)
#
## SOURCE statemachine


## GENERATE MOC
#qt5_wrap_cpp(ProjectUiSrcMoc
#        ${ProjectHeaderUi} # header files for ui
#)

#add_library(UiLib
#        ${ProjectHeaderUi}
#        ${ProjectUiSource}
#        ${ProjectUiSrcMoc}
#        ${ProjectUiFilesMoc}
#)


