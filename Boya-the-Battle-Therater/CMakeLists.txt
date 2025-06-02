# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(Boya-the-Battle-Therater)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED )
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
include_directories(
    .
)

set (SRCS
    archertower.h archertower.cpp
    areaattack.h areaattack.cpp
    attack.h
    enemy.h enemy.cpp
    gamewindow.h gamewindow.cpp
    generatepath.h
    goblin.h goblin.cpp
    magictower.h magictower.cpp
    main.cpp
    multifilestructure.h
    ogre.h ogre.cpp
    orc.h orc.cpp
    selectionframe.h selectionframe.cpp
    singletargetattack.h singletargetattack.cpp
    startwindow.h startwindow.cpp
    shaman.h shaman.cpp
    tower.h tower.cpp
    towerposition.h
    ui_startwindow.h
    resource.qrc
)


add_executable(Boya-the-Battle-Therater ${SRCS})

target_link_libraries(Boya-the-Battle-Therater PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets )
target_link_libraries(Boya-the-Battle-Therater PRIVATE Qt6::Multimedia)
