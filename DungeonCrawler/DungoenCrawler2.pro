QT       += core gui
QT       += core testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstraktui.cpp \
    active.cpp \
    button.cpp \
    character.cpp \
    chest.cpp \
    controller.cpp \
    door.cpp \
    dungeoncrawler.cpp \
    floor.cpp \
    graphicalui.cpp \
    guardcontroller.cpp \
    level.cpp \
    levelchanger.cpp \
    list.cpp \
    main.cpp \
    mainwindow.cpp \
    npc.cpp \
    npcguard.cpp \
    passive.cpp \
    pit.cpp \
    player.cpp \
    portal.cpp \
    ramp.cpp \
    startscreen.cpp \
    stationarycontroller.cpp \
    switch.cpp \
    terminalui.cpp \
    tile.cpp \
    wall.cpp

HEADERS += \
    abstraktui.h \
    active.h \
    button.h \
    character.h \
    chest.h \
    controller.h \
    door.h \
    dungeoncrawler.h \
    floor.h \
    graphicalui.h \
    guardcontroller.h \
    level.h \
    levelchanger.h \
    list.h \
    mainwindow.h \
    npc.h \
    npcguard.h \
    passive.h \
    pit.h \
    player.h \
    portal.h \
    ramp.h \
    startscreen.h \
    stationarycontroller.h \
    switch.h \
    terminalui.h \
    tile.h \
    wall.h

FORMS += \
    mainwindow.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
