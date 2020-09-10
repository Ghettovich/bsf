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

set(BsfTestService
        service/logservicetest.cpp
        service/logservicetest.h
        service/iodeviceservicetest.cpp
        service/iodeviceservicetest.h)

add_executable(BsfTest
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
