#-------------------------------------------------
#
# Project created by QtCreator 2019-04-14T16:27:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LR5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    coordinate.cpp \
    ihandler.cpp \
    controller.cpp \
    logwriter.cpp \
    handlerregistry.cpp \
    unitgraphics.cpp \
    arrowgraphics.cpp

HEADERS  += mainwindow.h \
    logwriter.h \
    derivedhandlers.h \
    ihandler.h \
    reader.h \
    basehandler.h \
    model.h \
    memento.h \
    writer.h \
    coordinate.h \
    myexception.h \
    controller.h \
    handlerregistry.h \
    unitgraphics.h \
    arrowgraphics.h

FORMS    += mainwindow.ui
