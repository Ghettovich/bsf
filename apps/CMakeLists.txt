set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network REQUIRED)

include_directories(../src)

add_executable(BsfAppExe
        bsfapp.cpp
        ${CMAKE_SOURCE_DIR}/src/resource/theme.qrc)

target_link_libraries(BsfAppExe
        src
        Qt5::Core
        Qt5::Widgets
        Qt5::Sql
        Qt::Network)