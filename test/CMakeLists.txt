cmake_minimum_required(VERSION 3.7...3.18)

project(BsfTest)
set(CMAKE_CXX_STANDARD 14)


set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(BsfTestDomain
        # DOMAIN
        domain/transformpayloadtest.cpp
        domain/transformpayloadtest.h)

#set(BsfTestFactory
#        ${CMAKE_SOURCE_DIR}/src/factory/iodeviceformfactory.cpp
#        ${CMAKE_SOURCE_DIR}/src/factory/iodeviceformfactory.h)


set(BsfTestDatabase
        repo/actionarduinorepotest.cpp
        repo/actionarduinorepotest.h
        repo/arduinorepotest.cpp
        repo/arduinorepotest.h
        repo/iodevicerepotest.cpp
        repo/iodevicerepotest.h
        repo/reciperepotest.cpp
        repo/reciperepotest.h
        repo/statecoderepotest.cpp
        repo/statecoderepotest.h)


set(BsfTestService
        service/iodeviceservicetest.cpp
        service/iodeviceservicetest.h
        service/logservicetest.cpp
        service/logservicetest.h
        service/networkservicetest.cpp
        service/networkservicetest.h)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)
if (Qt5Widgets_FOUND)

    add_executable(BsfTest
            ${BsfTestDomain}
            ${BsfTestDatabase}
            ${BsfTestService}
            recipetest.cpp
            recipetest.h
            AutoTest.cpp
            AutoTest.h)

    target_include_directories(BsfTest PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${Bsf_SOURCE_DIR} ${Bsf_BINARY_DIR})

    target_link_libraries(BsfTest PUBLIC
            Qt5::Test
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::Network
            Qt5::Sql)

    add_custom_command(
            TARGET BsfTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/data/bsfTest.db
            ${CMAKE_CURRENT_BINARY_DIR}/data/bsfTest.db)

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



