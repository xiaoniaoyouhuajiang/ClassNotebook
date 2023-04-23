TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lab5.cpp \
    ../../2/Lab2Tests/src/isoscelestriangle.cpp \
    ../../2/Lab2Tests/src/point2d.cpp \
    ../../2/Lab2Tests/src/polygon.cpp \
    ../../2/Lab2Tests/src/rectangle.cpp \
    ../../2/Lab2Tests/src/righttriangle.cpp \
    ../../2/Lab2Tests/src/shape.cpp \
    ../../2/Lab2Tests/src/square.cpp \
    ../../2/Lab2Tests/src/triangle.cpp

HEADERS += \
    lab5.h \
    ../../2/Lab2Tests/src/isoscelestriangle.h \
    ../../2/Lab2Tests/src/point2d.h \
    ../../2/Lab2Tests/src/polygon.h \
    ../../2/Lab2Tests/src/rectangle.h \
    ../../2/Lab2Tests/src/righttriangle.h \
    ../../2/Lab2Tests/src/shape.h \
    ../../2/Lab2Tests/src/square.h \
    ../../2/Lab2Tests/src/triangle.h
