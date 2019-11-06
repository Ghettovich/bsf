cmake_minimum_required(VERSION 3.0)
project(bsf)

set(CMAKE_CXX_STANDARD 14)

include_directories(incl)
include_directories(incl/controller)
include_directories(incl/data)
include_directories(incl/domain)
include_directories(incl/model)
include_directories(incl/repo)
include_directories(incl/ui/forms)
include_directories(incl/ui/tabs)

# find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets Network Sql)

# need this to include the auto generated ui_mainwindow.h
# file from the qt5_wrap_ui call below.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# create sources setters
set(project_controller_sources src/controller/relaycontroller.cpp)
set(project_data_sources src/data/dbmanager.cpp)
set(project_domain_sources src/domain/arduino.cpp src/domain/distantcensor.cpp src/domain/iodevice.cpp src/domain/weightcensor.cpp)
set(project_main_sources src/ui/mainwindow.cpp main.cpp)
set(project_model_sources src/model/logtablemodel.cpp)
set(project_repo_sources src/repo/relaymanager.cpp)
set(project_server_sources server.cpp)
set(project_ui_forms_sources src/ui/forms/deviceform.cpp src/ui/forms/devicemanager.cpp src/ui/forms/relayform.cpp)
set(project_ui_tabs_sources src/ui/tabs/arduinotab.cpp src/ui/tabs/controlpaneltab.cpp src/ui/tabs/iodevicetab.cpp src/ui/tabs/logtab.cpp src/ui/tabs/recipetab.cpp)
set(project_ui_widgets_sources src/ui/widgets/maintabbarwidget.cpp)
# create header setters

set(project_controller_headers incl/controller/relaycontroller.h)
set(project_data_headers incl/data/dbmanager.h)
set(project_domain_headers incl/domain/action.h incl/domain/arduino.h incl/domain/distantcensor.h incl/domain/iodevice.h incl/domain/weightcensor.h)
set(project_main_headers incl/ui/mainwindow.h)
set(project_model_headers incl/model/logtablemodel.h)
set(project_repo_headers incl/repo/relaymanager.h)
set(project_server_headers server.h)
set(project_ui_forms_header incl/ui/forms/deviceform.h incl/ui/forms/devicemanager.h incl/ui/forms/relayform.h)
set(project_ui_tabs_headers incl/ui/tabs/arduinotab.h incl/ui/tabs/controlpaneltab.h incl/ui/tabs/iodevicetab.h incl/ui/tabs/logtab.h incl/ui/tabs/recipetab.h)
set(project_ui_widgets_headers incl/ui/widgets/maintabbarwidget.h)
# inlcude project ui files
set(project_ui src/ui/mainwindow.ui src/ui/forms/devicewidget.ui src/ui/forms/testrelaywidget.ui)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources
        ${project_controller_headers}
        ${project_data_headers}
        ${project_domain_headers}
        ${project_main_headers}
        ${project_model_headers}
        ${project_repo_headers}
        ${project_server_headers}
        ${project_ui_forms_header}
        ${project_ui_tabs_headers}
        ${project_ui_widgets_headers})

add_executable(bsf
        ${project_controller_sources}
        ${project_controller_headers}
        ${project_data_sources}
        ${project_data_headers}
        ${project_domain_sources}
        ${project_domain_headers}
        ${project_main_sources}
        ${project_main_headers}
        ${project_model_sources}
        ${project_model_headers}
        ${project_repo_sources}
        ${project_repo_headers}
        ${project_server_sources}
        ${project_server_headers}
        ${project_ui_forms_sources}
        ${project_ui_forms_headers}
        ${project_ui_tabs_sources}
        ${project_ui_tabs_headers}
        ${project_ui_widgets_sources}
        ${project_ui_widgets_headers}
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
