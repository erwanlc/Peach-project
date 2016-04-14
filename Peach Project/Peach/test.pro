#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T15:45:51
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    player.cpp \
    enemy.cpp \
    brique.cpp \
    playerview.cpp \
    enemyview.cpp \
    piece.cpp \
    hud.cpp \
    blocksurprise.cpp \
    mushroomheart.cpp \
    blockheart.cpp \
    power.cpp \
    mushroompower.cpp \
    blockpower.cpp \
    blockdestructible.cpp \
    blocklimit.cpp \
    mario.cpp \
    blocktp.cpp \
    turtle.cpp \
    turtleview.cpp

HEADERS  += \
    game.h \
    player.h \
    enemy.h \
    brique.h \
    playerview.h \
    enemyview.h \
    piece.h \
    hud.h \
    blocksurprise.h \
    mushroomheart.h \
    blockheart.h \
    power.h \
    mushroompower.h \
    blockpower.h \
    blockdestructible.h \
    blocklimit.h \
    mario.h \
    blocktp.h \
    turtle.h \
    turtleview.h

FORMS    +=

RESOURCES += \
    res.qrc
