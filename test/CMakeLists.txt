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

set(BsfTestRepo
        ${CMAKE_SOURCE_DIR}/src/data/bsfdatabaseconfig.cpp
        ${CMAKE_SOURCE_DIR}/src/data/bsfdatabaseconfig.h
        ${CMAKE_SOURCE_DIR}/src/repo/logrepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/logrepo.h
        ${CMAKE_SOURCE_DIR}/src/repo/arduinorepo.cpp
        ${CMAKE_SOURCE_DIR}/src/repo/arduinorepo.h
        repo/arduinorepotest.cpp
        repo/arduinorepotest.h)

set(BsfTestService
        ${CMAKE_SOURCE_DIR}/src/service/logservice.cpp
        ${CMAKE_SOURCE_DIR}/src/service/logservice.h
        service/logservicetest.cpp
        service/logservicetest.h
        service/iodeviceservicetest.cpp
        service/iodeviceservicetest.h)

add_executable(BsfTest
        ${BsfTestDomain}
        ${BsfTestRepo}
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
