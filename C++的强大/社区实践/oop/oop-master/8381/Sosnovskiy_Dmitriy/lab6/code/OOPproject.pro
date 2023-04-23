#QT -= gui

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OOPproject
TEMPLATE = app

CONFIG += c++11
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        creatures_basic_interfaces.cpp \
        field.cpp \
        gamewindow.cpp \
        logger.cpp \
        main.cpp \
        units_concrete_classes.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    abstractfactory.h \
    attribute.h \
    base.h \
    base_unit_observer_interfaces.h \
    client_handler.h \
    clientinputdata.h \
    command.h \
    concrete_units_classes.h \
    creatures_basic_interfaces.h \
    custom_classes.h \
    enums.h \
    exception.h \
    field.h \
    fieldcomponent.h \
    fieldcomponent_creature_observer_interfaces.h \
    fieldwidget.h \
    fightmediator.h \
    game.h \
    gamefacade.h \
    gamewindow.h \
    iprintable.h \
    landscapes.h \
    logdata.h \
    logger.h \
    neutral_objects.h \
    neutral_objects_effects_strategies.h \
    rules.h \
    snapshot.h \
    units_interfaces.h

FORMS += \
    gamewindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
