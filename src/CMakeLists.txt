cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Bsf)

# DEFAULT DEBUG
set(CMAKE_BUILD_TYPE Debug)

# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ADDITIONAL PATHS TO  BE SEARCH FOR UI FILES
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui/**/*.ui)

# DEFINE GLOBAL TARGET FOR MOC
set(CMAKE_GLOBAL_AUTOGEN_TARGET BsfMoc)
set(CMAKE_GLOBAL_AUTOGEN_TARGET_NAME BsfMoc)


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

set(BsfDomain
        domain/action.cpp
        domain/arduino.cpp
        domain/iodevice.cpp
        domain/iodevicetype.cpp
        domain/log.cpp
        domain/recipe.cpp
        domain/statecode.cpp
        domain/transformpayload.cpp
        domain/weightcensor.cpp
        # DTO
        dto/arduinodto.cpp
        dto/iodevicedto.cpp
)

set(BsfUi
        # UI FILES -- MAIN
        ui/main/mainwindow.ui
        ui/main/mainwindow.cpp
        # TABS
        ui/tabs/arduinotab.cpp
        ui/tabs/iodevicetab.cpp
        ui/tabs/logtab.cpp
        ui/tabs/recipetab.cpp
        ui/tabs/statemachinetab.cpp
        # FORMS
        ui/forms/detectionsensorform.ui
        ui/forms/detectionsensorform.cpp
        ui/forms/deviceactionform.ui
        ui/forms/deviceactionform.cpp
        ui/forms/deviceform.ui
        ui/forms/deviceform.cpp
        ui/forms/iodeviceform.ui
        ui/forms/iodeviceform.cpp
        ui/forms/relayform.ui
        ui/forms/relayform.cpp
        ui/forms/weightsensorform.ui
        ui/forms/weightsensorform.cpp
)

set(BsfController
        controller/tab/tabcontroller.cpp
        controller/device/devicecontroller.cpp
)

set(BsfDatabase
        data/bsfdatabaseconfig.cpp
        repo/actionarduinorepo.cpp
        repo/arduinorepo.cpp
        repo/iodevicerepo.cpp
        repo/logrepo.cpp
        repo/reciperepo.cpp
        repo/statecoderepo.cpp
)

set(BsfStatemachine
        statemachine/events/recipedata.cpp
        statemachine/events/recipeinfo.cpp
        statemachine/bsfpavementmachine.cpp
        statemachine/fault.cpp
        statemachine/pavementstateobject.cpp
        statemachine/statemachine.cpp
        statemachine/statemachine.h
)

set(BsfService
        service/iodeviceservice.cpp
        service/logservice.cpp
        service/payloadservice.cpp
)


# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Network Sql REQUIRED)


# EXEQTABLE
add_executable(Bsf
        ui/main/main.cpp
        ${BsfDomain}
        ${BsfUi}
        ${BsfController}
        ${BsfDatabase}
        ${BsfService}
        ${BsfStatemachine}
        ${BsfMoc}
        factory/iodeviceformfactory.h
        factory/networkmanagerfactory.h
)


target_link_libraries(Bsf
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Sql> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(WIN32)


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


