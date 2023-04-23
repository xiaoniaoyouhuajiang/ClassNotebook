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

SOURCES += \
    Base/base.cpp \
    Base/compositeUnit.cpp \
    Landscape/forest.cpp \
    Landscape/mountain.cpp \
    Landscape/proxy.cpp \
    Landscape/river.cpp \
    NeutralObj/armor.cpp \
    NeutralObj/context.cpp \
    NeutralObj/medicine.cpp \
    NeutralObj/poison.cpp \
    NeutralObj/weapon.cpp \
    Units/Arrow/archer.cpp \
    Units/Arrow/shaman.cpp \
    Units/Cavelry/knigth.cpp \
    Units/Cavelry/rider.cpp \
    Units/Factory/creaturesarmy.cpp \
    Units/Factory/humanityarmy.cpp \
    Units/Infantry/ork.cpp \
    Units/Infantry/swardman.cpp \
    attackmediator.cpp \
    attributes.cpp \
    cell.cpp \
    command/basecommand.cpp \
    command/fieldcommand.cpp \
    command/gamecommand.cpp \
    createmediator.cpp \
    facade.cpp \
    game/game.cpp \
    game/gamemediator.cpp \
    main.cpp \
    mainwindow.cpp \
    moveMediator.cpp \
    playingfield.cpp \
    subject.cpp \
    unit.cpp

HEADERS += \
    Base/base.h \
    Base/compositeUnit.h \
    Landscape/forest.h \
    Landscape/landscape.h \
    Landscape/mountain.h \
    Landscape/proxy.h \
    Landscape/river.h \
    NeutralObj/armor.h \
    NeutralObj/context.h \
    NeutralObj/medicine.h \
    NeutralObj/neutralObj.h \
    NeutralObj/poison.h \
    NeutralObj/weapon.h \
    Units/Arrow/archer.h \
    Units/Arrow/arrow.h \
    Units/Arrow/shaman.h \
    Units/Cavelry/cavelry.h \
    Units/Cavelry/knigth.h \
    Units/Cavelry/rider.h \
    Units/Factory/abstractArmy.h \
    Units/Factory/creaturesArmy.h \
    Units/Factory/humanityArmy.h \
    Units/Infantry/infantry.h \
    Units/Infantry/ork.h \
    Units/Infantry/swardman.h \
    attackmediator.h \
    attributes.h \
    cell.h \
    command/basecommand.h \
    command/command.h \
    command/fieldcommand.h \
    command/gamecommand.h \
    convertEnum.h \
    createmediator.h \
    enums.h \
    facade.h \
    game/game.h \
    game/gamemediator.h \
    mainwindow.h \
    moveMediator.h \
    observer.h \
    playingfield.h \
    subject.h \
    unit.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
