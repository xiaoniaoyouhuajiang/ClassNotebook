
include(../gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

INCLUDEPATH += "../../../src"

HEADERS +=     tst_testcase1.h

SOURCES +=     main.cpp \
        ../../../src/shape.cpp \
        ../../../src/polygon.cpp \
        ../../../src/rectangle.cpp \
        ../../../src/triangle.cpp \
        ../../../src/square.cpp \
        ../../../src/point2d.cpp
