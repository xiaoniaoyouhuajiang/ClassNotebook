
CONFIG -= qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

TARGET = lab2GoogleTests

SOURCES += main.cpp \
    arc.cpp \
    ellipse.cpp \
    round.cpp \
    shape.cpp

HEADERS += \
    arc.h \
    ellipse.h \
    point.h \
    round.h \
    shape.h
