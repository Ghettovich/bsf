cmake_minimum_required(VERSION 3.7...3.18)

#project(BsfTest)
#set(CMAKE_CXX_STANDARD 14)


set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)



target_sources(src
        PRIVATE
        domain/transformpayloadtest.cpp
        PUBLIC
        domain/transformpayloadtest.h)

target_sources(src PRIVATE
        repo/actionarduinorepotest.cpp
        repo/arduinorepotest.cpp
        repo/iodevicerepotest.cpp
        repo/reciperepotest.cpp
        repo/statecoderepotest.cpp
        PUBLIC
        repo/actionarduinorepotest.h
        repo/arduinorepotest.h
        repo/iodevicerepotest.h
        repo/reciperepotest.h
        repo/statecoderepotest.h)


target_sources(src PRIVATE
        service/iodeviceservicetest.cpp
        service/logservicetest.cpp
        service/networkservicetest.cpp
        PUBLIC
        service/iodeviceservicetest.h
        service/logservicetest.h
        service/networkservicetest.h)


find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)
if (Qt5Widgets_FOUND)

    add_executable(BsfTest
            recipetest.cpp
            recipetest.h
            AutoTest.cpp
            AutoTest.h)

    target_link_libraries(BsfTest PUBLIC
            src
            Qt5::Test
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::Network
            Qt5::Sql)

    target_include_directories(BsfTest PUBLIC
            ${Bsf_INCLUDE_DIRS}
    )

    add_custom_command(
            TARGET BsfTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/resource/payload.json
            ${CMAKE_CURRENT_BINARY_DIR}/resource/payload.json)

    add_test(NAME BsfTest COMMAND BsfTest)
else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)



