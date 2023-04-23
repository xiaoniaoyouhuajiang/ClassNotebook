include (gtest_dependency.pri)
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lab2.cpp

HEADERS += \
    lab2.h \
    tst_lab2test.h
