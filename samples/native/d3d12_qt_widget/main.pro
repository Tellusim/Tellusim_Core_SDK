# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

TARGET = main
TEMPLATE = app

DESTDIR = ./
MOC_DIR = build
OBJECTS_DIR = build

CONFIG += c++11 console debug
QT += core gui widgets

QMAKE_CXXFLAGS += -DTS_DEBUG=1

INCLUDEPATH += ../../../include

exists(../../../source/Tellusim_x64d.lib) { LIBS += ../../../source/Tellusim_x64d.lib }
else { LIBS += ../../../lib/windows/x64/Tellusim_x64d.lib }
LIBS += dxgi.lib d3d12.lib

HEADERS += QD3D12Widget.h
SOURCES += QD3D12Widget.cpp main.cpp
