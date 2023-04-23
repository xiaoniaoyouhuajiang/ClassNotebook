QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/Artillery.cpp \
        source/Board.cpp \
        source/BoardUnit.cpp \
        source/BoardUnitFactory.cpp \
        source/Cavalry.cpp \
        source/Game.cpp \
        source/Grass.cpp \
        source/Infantry.cpp \
        source/PlayableBoardUnit.cpp \
        source/PongoBaseBoardUnit.cpp \
        source/PongoBoardUnit.cpp \
        source/Snow.cpp \
        source/Stone.cpp \
        source/TerrainBoardUnit.cpp \
        source/Tree.cpp \
        source/TreeLog.cpp \
        source/UItoBackendConnector.cpp \
        source/main.cpp

RESOURCES += qt/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/units/bush_01.png \
    images/units/mashrooms_01.png \
    images/units/stone_01.png \
    images/units/tree_01.png \
    images/units/tree_bottom_01.png \
    images/units/tree_log_01.png \
    images/units/tree_top_01.png \
    qt/Background.qml \
    qt/Board.qml \
    qt/BoardCellDelegate.qml \
    qt/BoardCellModel.qml \
    qt/GameMenu.qml \
    qt/MainMenu.qml \
    qt/MyButton.qml \
    qt/NewGameMenu.qml \
    qt/SettingsMenu.qml \
    qt/UnitStats.qml \
    qt/main.qml

HEADERS += \
    include/Artillery.h \
    include/Board.h \
    include/BoardUnit.h \
    include/BoardUnitFactory.h \
    include/Cavalry.h \
    include/Game.h \
    include/Grass.h \
    include/Infantry.h \
    include/PlayableBoardUnit.h \
    include/PongoBaseBoardUnit.h \
    include/PongoBoardUnit.h \
    include/Snow.h \
    include/Stone.h \
    include/TerrainBoardUnit.h \
    include/Tree.h \
    include/TreeLog.h \
    include/UItoBackendConnector.h

INCLUDEPATH += \
    include \
    "3rd party/"
