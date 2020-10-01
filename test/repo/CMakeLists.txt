cmake_minimum_required(VERSION 3.7...3.18)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        tst_actionarduinorepo.h
        tst_arduinorepo.h
        tst_iodevicerepo.h
        tst_logrepo.h
        tst_reciperepo.h
        tst_statecoderepo.h)

# TARGET SOURCES
target_sources(srcTestLib
        PRIVATE
        tst_actionarduinorepo.cpp
        tst_arduinorepo.cpp
        tst_iodevicerepo.cpp
        tst_logrepo.cpp
        tst_reciperepo.cpp
        tst_statecoderepo.cpp
        PUBLIC
        ${HEADER_LIST})

target_link_libraries(srcTestLib
        Qt5::Test
        Qt5::Core)

target_include_directories(srcTestLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/repo
        $<INSTALL_INTERFACE:repo>)  # <prefix>/include/mylib
