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
    tetris/model/tile.cpp \
    tetris/model/jtile.cpp \
    tetris/model/ltile.cpp \
    tetris/model/otile.cpp \
    tetris/model/ttile.cpp \
    tetris/model/ztile.cpp \
    tetris/model/stile.cpp \
    tetris/model/itile.cpp \
    tetris/model/board.cpp \
    tetris/controller/tetriscontroller.cpp \
    iogame.cpp \
    mainmenu.cpp \
    controller2048.cpp \
    board2048.cpp
HEADERS += \  
    tetris/model/tile.h \
    tetris/model/jtile.h \
    tetris/model/ltile.h \
    tetris/model/otile.h \
    tetris/model/ttile.h \
    tetris/model/ztile.h \
    tetris/model/stile.h \
    tetris/model/itile.h \
    tetris/model/board.h \
    tetris/controller/tetriscontroller.h \
    iogame.h \
    mainmenu.h \
    controller2048.h \
    board2048.h

FORMS += \
    mainmenu.ui \
    2048.ui \
    tetris/view/tetris.ui

RESOURCES += \
    resources.qrc

CONFIG += \
    resources_big
