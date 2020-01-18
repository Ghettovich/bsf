
#add_subdirectory(main)

# main source
#set(Project_src
#        ${PROJECT_SOURCE_DIR}/main/mainwindow.cpp
#)
#
## SET HEADERS
#set(Project_hdr
#        ${PROJECT_SOURCE_DIR}/main/mainwindow.h
#)

#set(SOURCES
#        forms/detectionsensorform.cpp
#        forms/deviceactionform.cpp
#        forms/deviceform.cpp
#        forms/iodeviceform.cpp
#        forms/relayform.cpp
#        forms/weightsensorform.cpp
#        main/mainwindow.cpp
#        tabs/arduinotab.cpp
#        tabs/controlpaneltab.cpp
#        tabs/iodevicetab.cpp
#        tabs/logtab.cpp
#        tabs/recipetab.cpp
#        tabs/statemachinetab.cpp
#        widgets/maintabbarwidget.cpp)
#
## GENERE MOC FOR UI FILES
#set(ProjectUi
#        ${PROJECT_SOURCE_DIR}/main/mainwindow.ui
#        ${PROJECT_SOURCE_DIR}forms/detectionsensorform.ui
##        ${PROJECT_SOURCE_DIR}forms/deviceform.ui
##        ${PROJECT_SOURCE_DIR}forms/relayform.ui
##        ${PROJECT_SOURCE_DIR}forms/deviceactionform.ui
##        ${PROJECT_SOURCE_DIR}forms/iodeviceform.ui
##        ${PROJECT_SOURCE_DIR}forms/weightsensorform.ui
#)
#
#qt5_wrap_cpp(Project_hdr_moc ${Project_hdr})
#qt5_wrap_ui(Project_ui_moc ${ProjectUi})
#
#add_library(UiLib SHARED
#        ${Project_src}
#        ${Project_hdr_moc}
#        ${Project_ui_moc}
#)