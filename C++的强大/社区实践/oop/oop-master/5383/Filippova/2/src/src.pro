CONFIG -= qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

TARGET = Lab2

SOURCES += main.cpp \
    ellipse.cpp \
    figure.cpp \
    point.cpp \
    rectangle.cpp \
    quare.cpp

HEADERS += \
    point.h \
    rectangle.h \
    square.h \
    figure.h \
    ellipse.h
