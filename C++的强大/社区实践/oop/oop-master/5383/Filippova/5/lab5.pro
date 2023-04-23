include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../2/src/ellipse.cpp \
    ../../2/src/figure.cpp \
    ../../2/src/point.cpp \
    ../../2/src/rectangle.cpp \
    ../../2/src/square.cpp

HEADERS += \
    5.h \
    tests.h \
    ../../2/src/ellipse.h \
    ../../2/src/figure.h \
    ../../2/src/point.h \
    ../../2/src/rectangle.h \
    ../../2/src/square.h
