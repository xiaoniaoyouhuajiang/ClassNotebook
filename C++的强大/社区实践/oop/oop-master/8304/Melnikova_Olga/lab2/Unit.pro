QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

FORMS += \
    creategamewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc \
    res.qrc

HEADERS += \
    creategamewindow.h \
    fabrics/damage.h \
    fabrics/health.h \
    fabrics/landscapefabric.h \
    fabrics/objectFabric.h \
    field/cell.h \
    field/field.h \
    field/fielditerator.h \
    game.h \
    landscapes/cliff.h \
    landscapes/cliffProxy.h \
    landscapes/glade.h \
    landscapes/gladeProxy.h \
    landscapes/landscape.h \
    landscapes/swamp.h \
    landscapes/swampProxy.h \
    mainwindow.h \
    objects/base.h \
    objects/neutral_objects/horse.h \
    objects/neutral_objects/medicinechest.h \
    objects/neutral_objects/neutralobject.h \
    objects/neutral_objects/powerup.h \
    objects/neutral_objects/shield.h \
    objects/object.h \
    objects/units/archer.h \
    objects/units/archery.h \
    objects/units/cavalry.h \
    objects/units/crossbowman.h \
    objects/units/heavyrider.h \
    objects/units/infantry.h \
    objects/units/knight.h \
    objects/units/lightrider.h \
    objects/units/spearman.h \
    objects/units/unit.h \
    observer/iobserver.h \
    observer/ipublisher.h \
    observer/observer.h \
    strategies/attackradiusincrease.h \
    strategies/enableshield.h \
    strategies/healthdecrease.h \
    strategies/healthincrease.h \
    strategies/istrategy.h \
    strategies/kill.h \
    strategies/movementradiusincrease.h

SOURCES += \
    creategamewindow.cpp \
    fabrics/damage.cpp \
    fabrics/health.cpp \
    fabrics/landscapefabric.cpp \
    fabrics/objectFabric.cpp \
    field/cell.cpp \
    field/field.cpp \
    field/fielditerator.cpp \
    game.cpp \
    landscapes/cliff.cpp \
    landscapes/cliffProxy.cpp \
    landscapes/glade.cpp \
    landscapes/gladeProxy.cpp \
    landscapes/landscape.cpp \
    landscapes/swamp.cpp \
    landscapes/swampProxy.cpp \
    main.cpp \
    mainwindow.cpp \
    objects/base.cpp \
    objects/neutral_objects/horse.cpp \
    objects/neutral_objects/medicinechest.cpp \
    objects/neutral_objects/neutralobject.cpp \
    objects/neutral_objects/powerup.cpp \
    objects/neutral_objects/shield.cpp \
    objects/object.cpp \
    objects/units/archer.cpp \
    objects/units/archery.cpp \
    objects/units/cavalry.cpp \
    objects/units/crossbowman.cpp \
    objects/units/heavyrider.cpp \
    objects/units/infantry.cpp \
    objects/units/knight.cpp \
    objects/units/lightrider.cpp \
    objects/units/spearman.cpp \
    objects/units/unit.cpp \
    observer/iobserver.cpp \
    observer/ipublisher.cpp \
    observer/observer.cpp \
    strategies/attackradiusincrease.cpp \
    strategies/enableshield.cpp \
    strategies/healthdecrease.cpp \
    strategies/healthincrease.cpp \
    strategies/istrategy.cpp \
    strategies/kill.cpp \
    strategies/movementradiusincrease.cpp
