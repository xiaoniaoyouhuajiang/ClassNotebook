include(../gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS +=     \
    ../../../src/ellipse.h \
    ../../../src/figure.h \
    ../../../src/point.h \
    ../../../src/rectangle.h \
    ../../../src/square.h \
    tst_squaretestset.h \
    tst_ellipsetestset.h \
    tst_rectangletestset.h

SOURCES +=     main.cpp \
    ../../../src/ellipse.cpp \
    ../../../src/figure.cpp \
    ../../../src/point.cpp \
    ../../../src/quare.cpp \
    ../../../src/rectangle.cpp
