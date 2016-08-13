CONFIG += console

QT += core gui
QT += widgets

TARGET = exception
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.hpp


include( $$PWD/../lua_source/lua_source.pri )
include( $$PWD/../LuaFullTest.pri )
DESTDIR=$$THIS_PROJECT_DESTDIR
