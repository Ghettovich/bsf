#cmake_minimum_required(VERSION 3.7...3.18)
#
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
#find_library(dataLib data
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(dataLib)
#
#    message("data lib found")
#
#else (!dataLib)
#    message("Could not find data lib")
#endif(dataLib)
#
#find_library(domainLib domain
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(domainLib)
#    message("Found lib")
#else (!domainLib)
#    message("Could not find domain lib")
#endif(domainLib)
#
#find_library(factoryLib factory
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(factoryLib)
#    message("Found factory lib")
#else (!factoryLib)
#    message("Could not find factory lib")
#endif(factoryLib)
#
#find_library(parserLib parser
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(parserLib)
#    message("Found parser lib")
#else (!parserLib)
#    message("Could not find factory lib")
#endif(parserLib)
#
#find_library(repoLib repo
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(repoLib)
#    message("Found repository lib")
#else (!repoLib)
#    message("Could not find repository lib")
#endif(repoLib)
#
#find_library(serviceLib service
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(serviceLib)
#    message("Found service lib")
#else (!serviceLib)
#    message("Could not find service lib")
#endif(serviceLib)
#
#find_library(statemachineLib statemachine
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(statemachineLib)
#    message("Found statemachine lib")
#else (!statemachineLib)
#    message("Could not find statemachine lib")
#endif(statemachineLib)
#
#find_library(uiLib ui
#        HINTS "${CMAKE_BINARY_DIR}/")
#
#if(uiLib)
#    message("Found ui lib")
#else (!uiLib)
#    message("Could not find ui lib")
#endif(uiLib)
#
## find Qt5 and required components | Qt5_DIR
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
#
#if (Qt5Widgets_FOUND)
#
#    add_executable(BsfAppExe
#            ${CMAKE_SOURCE_DIR}/apps/bsfapp.cpp
#            ${CMAKE_SOURCE_DIR}/src/resource/theme.qrc)
#
#    target_include_directories(BsfAppExe PRIVATE
#            ${Bsf_SOURCE_DIR}/src/ui_autogen/include)
#
#    target_link_libraries(BsfAppExe
#            dataLib
#            domainLib
#            factoryLib
#            parserLib
#            repoLib
#            serviceLib
#            statemachineLib
#            uiLib
#            Qt5::Widgets)
#
#    # COPY DATABASE
#    add_custom_command(
#            TARGET BsfAppExe POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${PROJECT_SOURCE_DIR}/data/bsf.db
#            ${CMAKE_CURRENT_BINARY_DIR}/data/bsf.db)
#
#else (!Qt5Widgets_FOUND)
#    # OOPS
#    message("could not find qt widgets")
#endif (Qt5Widgets_FOUND)