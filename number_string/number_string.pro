CONFIG += console

QT += core gui
QT += widgets

TARGET = number_string
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.hpp

include( $$PWD/part_goole_v8/double-conversion.pri )
include( $$PWD/../lua_source/lua_source.pri )
include( $$PWD/../LuaFullTest.pri )
DESTDIR=$$THIS_PROJECT_DESTDIR


