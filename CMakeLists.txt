cmake_minimum_required(VERSION 3.15)
project(bsf)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)
include_directories(forms)
include_directories(headers)
include_directories(headers/domain)
include_directories(headers/models)
include_directories(headers/tabs)
include_directories(headers/tabs/main)

# find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets Network Sql)

# need this to include the auto generated ui_mainwindow.h
# file from the qt5_wrap_ui call below.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(project_sources data/dbmanager.cpp models/logtablemodel.cpp tabs/main/arduinotab.cpp tabs/main/controlpaneltab.cpp tabs/main/iodevicetab.cpp tabs/main/logtab.cpp tabs/main/recipetab.cpp mainwindow.cpp main.cpp maintabbarwidget.cpp server.cpp forms/deviceform.cpp domain/arduino.cpp domain/iodevice.cpp domain/weightcensor.cpp)
set(project_headers data/dbmanager.h headers/domain/arduino.h headers/domain/distantcensor.h headers/domain/iodevice.h headers/domain/weightcensor.h headers/models/logtablemodel.h headers/tabs/main/arduinotab.h headers/tabs/main/controlpaneltab.h headers/tabs/main/iodevicetab.h headers/tabs/main/logtab.h headers/tabs/main/recipetab.h maintabbarwidget.h mainwindow.h server.h forms/deviceform.h)
set(project_ui mainwindow.ui devicewidget.ui)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})
add_executable(bsf
        ${project_sources}
        ${project_headers}
        ${ui_wrap}
        ${moc_sources})
target_link_libraries(bsf
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Sql> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
