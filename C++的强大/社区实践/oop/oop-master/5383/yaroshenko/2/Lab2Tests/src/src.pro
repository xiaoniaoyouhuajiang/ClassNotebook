
CONFIG -= qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

TARGET = Lab2Tests

SOURCES += main.cpp \
        shape.cpp \
        polygon.cpp \
        rectangle.cpp \
        square.cpp \
        triangle.cpp \
        righttriangle.cpp \
        isoscelestriangle.cpp \
        point2d.cpp \

HEADERS += shape.h \
        polygon.h \
        rectangle.h \
        square.h \
        triangle.h \
        righttriangle.h \
        isoscelestriangle.h \
        point2d.h

