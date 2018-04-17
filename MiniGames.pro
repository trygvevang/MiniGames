QT       += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniGames
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    tile.cpp \
    jtile.cpp \
    ltile.cpp \
    otile.cpp \
    ttile.cpp \
    ztile.cpp \
    stile.cpp \
    itile.cpp \
    board.cpp \
    tetriscontroller.cpp \
    iogame.cpp \
    mainmenu.cpp \
    controller2048.cpp \
    board2048.cpp
HEADERS += \  
    tile.h \
    jtile.h \
    ltile.h \
    otile.h \
    ttile.h \
    ztile.h \
    stile.h \
    itile.h \
    board.h \
    iogame.h \
    mainmenu.h \
    tetriscontroller.h \
    controller2048.h \
    board2048.h

FORMS += \
    tetris.ui \
    mainmenu.ui \
    2048.ui

RESOURCES += \
    resources.qrc

CONFIG += \
    resources_big
