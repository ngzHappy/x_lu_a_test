QT -= core
QT -= gui

TARGET = lua_wrap
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app



include( $$PWD/../lua_source/lua_source.pri )
include( $$PWD/../LuaFullTest.pri )
DESTDIR=$$THIS_PROJECT_DESTDIR

SOURCES += \
    main.cpp






