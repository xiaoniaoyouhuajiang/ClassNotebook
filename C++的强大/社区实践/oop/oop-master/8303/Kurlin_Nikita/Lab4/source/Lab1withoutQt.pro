TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Units/Archers/archers.cpp \
    Units/Archers/flatbow.cpp \
    Units/Archers/longbow.cpp \
    Units/Cavalry/cavalry.cpp \
    Units/Cavalry/dragoon.cpp \
    Units/Cavalry/hussar.cpp \
    Units/Infantry/infantry.cpp \
    Units/Infantry/spearman.cpp \
    Units/Infantry/swordsman.cpp \
    Units/unit.cpp \
    base.cpp \
    compositeunit.cpp \
    gamefield.cpp \
    iterator.cpp \
    main.cpp \
    subject.cpp \
    mediator.cpp \
    facade.cpp \
    logger.cpp \
    adapter.cpp \
    loggerproxy.cpp \
    fieldsnapshot.cpp

HEADERS += \
    Landscapes/forests.h \
    Landscapes/landscape.h \
    Landscapes/landscapeprotected.h \
    Landscapes/mountains.h \
    Landscapes/rivers.h \
    NeutralObject/armor.h \
    NeutralObject/medicine.h \
    NeutralObject/neutralobject.h \
    NeutralObject/poison.h \
    NeutralObject/weapon.h \
    Units/Archers/archers.h \
    Units/Archers/flatbow.h \
    Units/Archers/longbow.h \
    Units/Cavalry/cavalry.h \
    Units/Cavalry/dragoon.h \
    Units/Cavalry/hussar.h \
    Units/Infantry/infantry.h \
    Units/Infantry/spearman.h \
    Units/Infantry/swordsman.h \
    Units/unit.h \
    UnitsFactory/archersfactory.h \
    UnitsFactory/cavalryfactory.h \
    UnitsFactory/infantryfactory.h \
    UnitsFactory/unitfactory.h \
    attributes.h \
    base.h \
    basehandler.h \
    compositeunit.h \
    gamefield.h \
    iterator.h \
    observer.h \
    subject.h \
    command.h \
    mediator.h \
    basecomponent.h \
    facade.h \
    logger.h \
    adapter.h \
    loggerproxy.h \
    file.h \
    fieldsnapshot.h \
    filein.h
