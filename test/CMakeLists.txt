project(BsfTest LANGUAGES CXX)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
)

enable_testing(true)

set(BsfTestDomain
        ${CMAKE_SOURCE_DIR}/src/domain/action.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/action.h
        ${CMAKE_SOURCE_DIR}/src/domain/arduino.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/arduino.h
        ${CMAKE_SOURCE_DIR}/src/domain/bafalog.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/bafalog.h
        ${CMAKE_SOURCE_DIR}/src/domain/detectionsensor.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/detectionsensor.h
        ${CMAKE_SOURCE_DIR}/src/domain/iodevice.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/iodevice.h
        ${CMAKE_SOURCE_DIR}/src/domain/iodevicetype.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/iodevicetype.h
        ${CMAKE_SOURCE_DIR}/src/domain/recipe.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/recipe.h
        ${CMAKE_SOURCE_DIR}/src/domain/relay.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/relay.h
        ${CMAKE_SOURCE_DIR}/src/domain/statecode.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/statecode.h
        ${CMAKE_SOURCE_DIR}/src/domain/transformpayload.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/transformpayload.h
        ${CMAKE_SOURCE_DIR}/src/domain/weightcensor.cpp
        ${CMAKE_SOURCE_DIR}/src/domain/weightcensor.h
        # DTO
        ${CMAKE_SOURCE_DIR}/src/dto/arduinodto.cpp
        ${CMAKE_SOURCE_DIR}/src/dto/arduinodto.h
        ${CMAKE_SOURCE_DIR}/src/dto/iodevicedto.cpp
        ${CMAKE_SOURCE_DIR}/src/dto/iodevicedto.h)

set(BsfTestFactory
        ${CMAKE_SOURCE_DIR}/src/factory/iodeviceformfactory.cpp
        ${CMAKE_SOURCE_DIR}/src/factory/iodeviceformfactory.h)

set(BsfTestUi
        # CONTROLLER
        ${CMAKE_SOURCE_DIR}/src/controller/tab/tabcontroller.h
        ${CMAKE_SOURCE_DIR}/src/controller/tab/tabcontroller.cpp
        # UI FILES -- MAIN
        ${CMAKE_SOURCE_DIR}/src/ui/main/mainwindow.ui
        ${CMAKE_SOURCE_DIR}/src/ui/main/mainwindow.h
        ${CMAKE_SOURCE_DIR}/src/ui/main/mainwindow.cpp
        # TABS
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/arduinotab.h
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/arduinotab.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/iodevicetab.h
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/iodevicetab.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/logtab.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/logtab.h
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/recipetab.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/recipetab.h
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/statemachinetab.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/tabs/statemachinetab.h
        # TABWIDGET
        ${CMAKE_SOURCE_DIR}/src/ui/tabwidget/statemachinetabwidget.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/tabwidget/statemachinetabwidget.h
        # FORMS
        ${CMAKE_SOURCE_DIR}/src/ui/forms/detectionsensorform.ui
        ${CMAKE_SOURCE_DIR}/src/ui/forms/detectionsensorform.h
        ${CMAKE_SOURCE_DIR}/src/ui/forms/detectionsensorform.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/forms/deviceactionform.ui
        ${CMAKE_SOURCE_DIR}/src/ui/forms/deviceactionform.h
        ${CMAKE_SOURCE_DIR}/src/ui/forms/deviceactionform.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/forms/deviceform.ui
        ${CMAKE_SOURCE_DIR}/src/ui/forms/deviceform.h
        ${CMAKE_SOURCE_DIR}/src/ui/forms/deviceform.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/forms/iodeviceform.ui
        ${CMAKE_SOURCE_DIR}/src/ui/forms/iodeviceform.h
        ${CMAKE_SOURCE_DIR}/src/ui/forms/iodeviceform.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/forms/relayform.ui
        ${CMAKE_SOURCE_DIR}/src/ui/forms/relayform.h
        ${CMAKE_SOURCE_DIR}/src/ui/forms/relayform.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/forms/weightsensorform.ui
        ${CMAKE_SOURCE_DIR}/src/ui/forms/weightsensorform.h
        ${CMAKE_SOURCE_DIR}/src/ui/forms/weightsensorform.cpp)

set(BsfUiStateWidgets
        ${CMAKE_SOURCE_DIR}/src/ui/statewidgets/selectrecipe.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/statewidgets/selectrecipe.h
        ${CMAKE_SOURCE_DIR}/src/ui/statewidgets/statemachinepage.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/statewidgets/statemachinepage.h
        ${CMAKE_SOURCE_DIR}/src/ui/statewidgets/weightrecipe.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/statewidgets/weightrecipe.h)

set(BsfTestDatabase
        ${CMAKE_SOURCE_DIR}/src/data/bsfdatabaseconfig.cpp
        ${CMAKE_SOURCE_DIR}/src/data/bsfdatabaseconfig.h
        repo/actionarduinorepotest.cpp
        repo/actionarduinorepotest.h
        ${CMAKE_SOURCE_DIR}/src/repo/actionarduinorepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/actionarduinorepo.h
        repo/arduinorepotest.cpp
        repo/arduinorepotest.h
        ${CMAKE_SOURCE_DIR}/src/repo/arduinorepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/arduinorepo.h
        repo/iodevicerepotest.cpp
        repo/iodevicerepotest.h
        ${CMAKE_SOURCE_DIR}/src/repo/iodevicerepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/iodevicerepo.h
        ${CMAKE_SOURCE_DIR}/src/repo/logrepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/logrepo.h
        repo/reciperepotest.cpp
        repo/reciperepotest.h
        ${CMAKE_SOURCE_DIR}/src/repo/reciperepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/reciperepo.h
        repo/statecoderepotest.cpp
        repo/statecoderepotest.h
        ${CMAKE_SOURCE_DIR}/src/repo/statecoderepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/statecoderepo.h)


set(BsfTestStatemachine
        ${CMAKE_SOURCE_DIR}/src/statemachine/events/recipedata.cpp
        ${CMAKE_SOURCE_DIR}/src/statemachine/events/recipedata.h
        ${CMAKE_SOURCE_DIR}/src/statemachine/events/recipeinfo.cpp
        ${CMAKE_SOURCE_DIR}/src/statemachine/events/recipeinfo.h
        ${CMAKE_SOURCE_DIR}/src/statemachine/bsfpavementmachine.cpp
        ${CMAKE_SOURCE_DIR}/src/statemachine/bsfpavementmachine.h
        ${CMAKE_SOURCE_DIR}/src/statemachine/datatypes.h
        ${CMAKE_SOURCE_DIR}/src/statemachine/fault.cpp
        ${CMAKE_SOURCE_DIR}/src/statemachine/fault.h
        ${CMAKE_SOURCE_DIR}/src/statemachine/pavementstateobject.cpp
        ${CMAKE_SOURCE_DIR}/src/statemachine/pavementstateobject.h
        ${CMAKE_SOURCE_DIR}/src/statemachine/statemachine.cpp
        ${CMAKE_SOURCE_DIR}/src/statemachine/statemachine.h)

set(BsfTestService
        service/iodeviceservicetest.cpp
        service/iodeviceservicetest.h
        ${CMAKE_SOURCE_DIR}/src/service/iodeviceservice.cpp
        ${CMAKE_SOURCE_DIR}/src/service/iodeviceservice.h
        service/logservicetest.cpp
        service/logservicetest.h
        ${CMAKE_SOURCE_DIR}/src/service/logservice.cpp
        ${CMAKE_SOURCE_DIR}/src/service/logservice.h
        ${CMAKE_SOURCE_DIR}/src/service/networkservice.cpp
        ${CMAKE_SOURCE_DIR}/src/service/networkservice.h
        ${CMAKE_SOURCE_DIR}/src/service/payloadservice.cpp
        ${CMAKE_SOURCE_DIR}/src/service/payloadservice.h)

add_executable(BsfTest
        ${BsfTestDomain}
        ${BsfTestFactory}
        ${BsfTestUi}
        ${BsfUiStateWidgets}
        ${BsfTestDatabase}
        ${BsfTestStatemachine}
        ${BsfTestService}
        recipetest.cpp
        recipetest.h
        AutoTest.cpp
        AutoTest.h)

target_include_directories(BsfTest PUBLIC
        Qt5Widgets_INCLUDE_DIRS)

target_link_libraries(BsfTest
        Qt5::Test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql)

configure_file(data/bsfTest.db data/bsfTest.db COPYONLY)

add_test(NAME BsfTest COMMAND BsfTest)
