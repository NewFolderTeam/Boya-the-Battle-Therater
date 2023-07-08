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
    archertower1.cpp
    archertower1.h
    archertower2.cpp
    archertower2.h
    archertower3.cpp
    archertower3.h
    enemy.cpp
    enemy.h
    gamewindow.cpp
    gamewindow.h
    generatepath.h
    goblin.cpp
    goblin.h
    magictower1.cpp
    magictower1.h
    magictower2.cpp
    magictower2.h
    magictower3.cpp
    magictower3.h
    main.cpp
    ogre.cpp
    ogre.h
    multifilestructure.h
    orc.cpp
    orc.h
    selectionframe.cpp
    selectionframe.h
    startwindow.cpp
    startwindow.h
    shaman.cpp
    shaman.h
    tower.cpp
    tower.h
    towerposition.h
    ui_startwindow.h
    resource.qrc
)


add_executable(Boya-the-Battle-Therater ${SRCS})

target_link_libraries(Boya-the-Battle-Therater PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets )
target_link_libraries(Boya-the-Battle-Therater PRIVATE Qt6::Multimedia)
