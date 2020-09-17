cmake_minimum_required(VERSION 3.7...3.18)

set(CMAKE_CXX_STANDARD 14)


add_executable(BsfApp bsfapp.cpp)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    target_link_libraries(BsfApp
            bsfLib
            Qt5::Widgets)

    # All users of this library will need at least C++14
    target_compile_features(BsfApp PUBLIC cxx_std_14)


    # COPY DATABASE
#    add_custom_command(
#            TARGET BsfApp POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${PROJECT_SOURCE_DIR}/data/bsf.db
#            ${CMAKE_CURRENT_BINARY_DIR}/data/bsf.db)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)