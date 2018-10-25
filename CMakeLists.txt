cmake_minimum_required(VERSION 2.8.3)
project(interpreter_gui)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
set(QT_LIBRARIES Qt5::Widgets)
set(QT_LIBRARIES Qt5::Core)
set(QT_LIBRARIES Qt5::Gui)


catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES interpreter_gui
  CATKIN_DEPENDS
  roscpp
  std_msgs
#  DEPENDS system_lib
)

link_directories(
     ${GTKMM_LIBRARY_DIRS}  #es la interfaz C++ oficial para
                            #la popular biblioteca de interfaz gráfica GTK+.
     ${catkin_LIBRARY_DIRS}
    )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    include
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${catkin_INCLUDE_DIRS}
    ${roscpp_INCLUDE_DIRS}

)
include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

set (MyProject_src
          src/main.cpp
          src/codeeditor.cpp
          src/completelistwidget.cpp
          src/console.cpp
          src/highlighter.cpp
          src/mainwindow.cpp
    )

set (MyProjectLib_ui
          ui/mainwindow.ui
    )

set (MyProjectLib_hdr

            include/codeeditor.h
            include/completelistwidget.h
            include/console.h
            include/highlighter.h
            include/mainwindow.h
            include/ui_mainwindow.h

    )

set (MyProjectLib_qrc
           image.qrc
    )
QT5_WRAP_CPP(MyProjectLib_hdr_MOC ${MyProjectLib_hdr})
QT5_WRAP_UI(MyProjectLib_ui_MOC ${MyProjectLib_ui})
QT5_ADD_RESOURCES(MyProjectLib_qrc_MOC ${MyProjectLib_qrc})

add_executable(interpreter_gui  ${MyProject_src}  ${MyProjectLib_hdr_MOC} ${MyProjectLib_ui_MOC} ${MyProjectLib_qrc_MOC})

target_link_libraries(interpreter_gui
                         ${QT_LIBRARIES}   #Llamado QT Libraries
                         ${catkin_LIBRARIES}
                         Qt5::Widgets
                         Qt5::Core
                         Qt5::Gui
 )

add_definitions(-std=c++11
                )
