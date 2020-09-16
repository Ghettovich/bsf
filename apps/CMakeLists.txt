#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
#target_sources(bsfLib
#        PRIVATE
#            "${CMAKE_SOURCE_DIR}/src/ui/main/main.cpp"
#        )
#
#add_executable(BsfApp
#        ${CMAKE_SOURCE_DIR}/src/resource/theme.qrc)
#
##target_compile_features(BsfApp PRIVATE cxx_std_14)
#
## find Qt5 and required components | Qt5_DIR
#find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)
#
#if (Qt5Widgets_FOUND)
#
#    target_include_directories(BsfApp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
#
#    target_link_libraries(BsfApp PUBLIC
#            Qt5::Core
#            Qt5::Gui
#            Qt5::Widgets
#            Qt5::Network
#            Qt5::Sql)
#
#    add_custom_command(
#            TARGET BsfApp POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${PROJECT_SOURCE_DIR}/data/bsf.db
#            ${CMAKE_BINARY_DIR}/data/bsf.db)
#
#
#else (!Qt5Widgets_FOUND)
#    # OOPS
#    message("could not find qt widgets")
#endif (Qt5Widgets_FOUND)
#
