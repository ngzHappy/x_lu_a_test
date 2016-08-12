QT -= core
QT -= gui

TARGET = lua
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += $$PWD/../lua_source/lua.project.cxx

include( $$PWD/../lua_source/lua_source.pri )
include( $$PWD/../LuaFullTest.pri )
DESTDIR=$$THIS_PROJECT_DESTDIR






