cmake_minimum_required(VERSION 3.0)
project(bsf)

set(CMAKE_CXX_STANDARD 14)

include_directories(incl)
include_directories(incl/controller)
include_directories(incl/data)
include_directories(incl/domain)
include_directories(incl/factory)
include_directories(incl/repo)
include_directories(incl/service)
include_directories(incl/ui)
include_directories(incl/ui/forms)
include_directories(incl/ui/tabs)
include_directories(incl/ui/widgets)

# find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets Network Sql)

# need this to include the auto generated ui_mainwindow.h
# file from the qt5_wrap_ui call below.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# new structure
# main sources
set(project_main_sources src/ui/mainwindow.cpp main.cpp)
set(project_main_headers incl/ui/mainwindow.h)

# set project ui sources
set(project_ui_forms_sources src/ui/forms/detectionsensorform.cpp src/ui/forms/deviceactionform.cpp src/ui/forms/deviceform.cpp src/ui/forms/iodeviceform.cpp src/ui/forms/relayform.cpp src/ui/forms/weightsensorform.cpp)
set(project_ui_tabs_sources src/ui/tabs/arduinotab.cpp src/ui/tabs/controlpaneltab.cpp src/ui/tabs/iodevicetab.cpp src/ui/tabs/logtab.cpp src/ui/tabs/recipetab.cpp)
set(project_ui_widgets_sources src/ui/widgets/maintabbarwidget.cpp)

# set project ui headers
set(project_ui_forms_header incl/ui/forms/detectionsensorform.h incl/ui/forms/deviceactionform.h incl/ui/forms/deviceform.h incl/ui/forms/iodeviceform.h incl/ui/forms/relayform.h incl/ui/forms/weightsensorform.h)
set(project_ui_tabs_headers incl/ui/tabs/arduinotab.h incl/ui/tabs/controlpaneltab.h incl/ui/tabs/iodevicetab.h incl/ui/tabs/logtab.h incl/ui/tabs/recipetab.h)
set(project_ui_widgets_headers incl/ui/widgets/maintabbarwidget.h)
# set project ui controller header

# project domain
set(project_domain_headers incl/domain/action.h incl/domain/arduino.h incl/domain/detectioncensor.h incl/domain/iodevice.h incl/domain/iodevicetype.h incl/domain/transformpayload.h incl/domain/log.h incl/domain/statecode.h incl/domain/weightcensor.h)
set(project_domain_sources src/domain/transformpayload.cpp)

# data sources
set(project_data incl/data/bsfdatabaseconfig.h src/data/bsfdatabaseconfig.cpp)

# DTO
set(project_dto incl/dto/iodevicedto.h)

# factory
set(project_factories incl/factory/iodeviceformfactory.h incl/factory/networkmanagerfactory.h)

# log
#set(project_log incl/log/bsflog.h incl/domain/log.h src/log/bsflog.cpp src/domain/log.cpp)

# controller
set(project_controller incl/controller/devicecontroller.h incl/controller/tabcontroller.h src/controller/devicecontroller.cpp src/controller/tabcontroller.cpp)
#set(project_controller_src src/controller/devicecontroller.cpp src/controller/tabcontroller.cpp)

# model
#set(project_model incl/model/logtablemodel.h)

# repositories
set(project_repositories incl/repo/actionarduinorepo.h incl/repo/arduinorepo.h incl/repo/statecoderepo.h incl/repo/iodevicerepo.h incl/repo/logrepo.h src/repo/actionarduinorepo.cpp src/repo/arduinorepo.cpp src/repo/statecoderepo.cpp src/repo/iodevicerepo.cpp src/repo/logrepo.cpp)

# service
set(project_service incl/service/iodeviceservice.h incl/service/logservice.h incl/service/payloadservice.h)
set(project_service_src src/service/iodeviceservice.cpp src/service/logservice.cpp src/service/payloadservice.cpp)


# inlcude project ui files
set(project_ui src/ui/mainwindow.ui src/ui/forms/detectionsensorform.ui src/ui/forms/deviceform.ui src/ui/forms/relayform.ui src/ui/forms/deviceactionform.ui src/ui/forms/iodeviceform.ui src/ui/forms/weightsensorform.ui)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources
        ${project_controller}
        ${project_main_headers}
        ${project_ui_forms_header}
        ${project_ui_tabs_headers}
        ${project_ui_widgets_headers}
        ${project_service})

add_executable(bsf
        ${project_main_sources}
        ${project_main_headers}
        ${project_data}
        ${project_domain_headers}
        ${project_domain_sources}
        ${project_dto}
        ${project_factories}
        ${project_controller}
        ${project_repositories}
        ${project_service_src}
        ${ui_wrap}
        ${moc_sources}
        ${project_ui_forms_sources}
        ${project_ui_forms_headers}
        ${project_ui_tabs_sources}
        ${project_ui_tabs_headers}
        ${project_ui_widgets_sources}
        ${project_ui_widgets_headers})

target_link_libraries(bsf
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql)
if(WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Sql> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(WIN32)