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
    Adapter.cpp \
    Base.cpp \
    Factory.cpp \
    FieldBlock.cpp \
    File.cpp \
    Game.cpp \
    GameField.cpp \
    Landscape.cpp \
    Logger.cpp \
    Memento.cpp \
    Neutral.cpp \
    NeutralFactory.cpp \
    ProxyLogger.cpp \
    Rules.cpp \
    Units.cpp \
    chainOfResposibility.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Adapter.h \
    Base.h \
    Factory.h \
    FieldBlock.h \
    File.h \
    Game.h \
    GameField.h \
    Landscape.h \
    Logger.h \
    Memento.h \
    Neutral.h \
    NeutralFactory.h \
    ProxyLogger.h \
    Rules.h \
    Units.h \
    chainOfResponsibility.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
