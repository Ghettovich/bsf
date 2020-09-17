cmake_minimum_required(VERSION 3.7...3.18)

set(CMAKE_CXX_STANDARD 14)

# Define library to which we will target sources
#add_library(bsflib "")

add_subdirectory(data)
add_subdirectory(domain)
add_subdirectory(factory)
add_subdirectory(parser)
add_subdirectory(repo)
add_subdirectory(service)
add_subdirectory(statemachine)
add_subdirectory(ui)

add_executable(BsfApp ui/main/main.cpp)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

if (Qt5Widgets_FOUND)

    target_include_directories(BsfApp PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${Bsf_SOURCE_DIR})

    target_link_libraries(BsfApp PUBLIC
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::Network
            Qt5::Sql)



    #include()
#
#    target_include_directories(bsflib PUBLIC
#            "${PROJECT_BINARY_DIR}"
#            ${EXTRA_INCLUDES}
#            Qt5Widgets_INCLUDE_DIRS
#            autogen
#            )

    # All users of this library will need at least C++14
    #target_compile_features(bsflib PUBLIC cxx_std_14)


    # COPY DATABASE
#    add_custom_command(
#            TARGET bsflib POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${PROJECT_SOURCE_DIR}/data/bsf.db
#            ${CMAKE_CURRENT_BINARY_DIR}/data/bsf.db)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

