#-------------------------------------------------
#
# Project created by QtCreator 2020-02-09T19:39:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheGame
TEMPLATE = app


SOURCES += main.cpp\
    Base/Base.cpp \
    Base/BaseSnapshot.cpp \
    Command/Command.cpp \
    Field/Cell.cpp \
    Field/Field.cpp \
    Field/FieldIterator.cpp \
    Field/FieldSnapshot.cpp \
    Field/RoutePlotter.cpp \
    Game/Game.cpp \
    Game/GameDestroyer.cpp \
    Game/GameFacade.cpp \
    Game/GameMediator.cpp \
    Game/Initializer.cpp \
    Game/Loader.cpp \
    Game/Saver.cpp \
    Handler/RouteHandler.cpp \
    Handler/UnitActionHandler.cpp \
    Handler/UnitBaseAttackHandler.cpp \
    Handler/UnitBaseHandler.cpp \
    Handler/UnitLandscapeHandler.cpp \
    Handler/UnitUnitAttackHandler.cpp \
    Handler/UnitUnitHandler.cpp \
    Handler/UnitUnitUnionHandler.cpp \
    Landscape/Forest.cpp \
    Landscape/ForestHill.cpp \
    Landscape/Hill.cpp \
    Landscape/ILandscape.cpp \
    Landscape/Landscape.cpp \
    Landscape/LandscapeFactory.cpp \
    Landscape/LandscapeProxy.cpp \
    Landscape/Mountain.cpp \
    Landscape/Plain.cpp \
    Landscape/Water.cpp \
    Log/LogAdapter.cpp \
    Log/Logger.cpp \
    Log/LoggerProxy.cpp \
    Log/Time.cpp \
    Neutrals/NeutralContext.cpp \
    Neutrals/NeutralObject.cpp \
    Neutrals/NeutralSnapshot.cpp \
    Player/NeutralPlayer.cpp \
    Player/Player.cpp \
    Player/PlayerSnapshot.cpp \
    Player/PlayerState.cpp \
    Rules/EliminationRule.cpp \
    Rules/Rule.cpp \
    Rules/SpeedRule.cpp \
    Trivia/Attributes.cpp \
    Trivia/Point.cpp \
    Trivia/Snapshot.cpp \
    UI/AttributeWidget.cpp \
    UI/BaseWidget.cpp \
    UI/LoggingWindow.cpp \
    UI/MainWindow.cpp \
    UI/ModifiedScene.cpp \
    UI/ModifiedView.cpp \
    UI/NewGameWindow.cpp \
    UI/PlayerWidget.cpp \
    UI/TurnButton.cpp \
    UI/VisualItem.cpp \
    UI/WinnerWindow.cpp \
    Unit/IUnit.cpp \
    Unit/Melee.cpp \
    Unit/Ranged.cpp \
    Unit/SiegeEngine.cpp \
    Unit/Unit.cpp \
    Unit/UnitFactory.cpp \
    Unit/UnitGroup.cpp \
    Unit/UnitGroupSnapshot.cpp \
    Unit/UnitSnapshot.cpp

HEADERS  += \
    Base/Base.h \
    Command/Command.h \
    Field/Cell.h \
    Field/Field.h \
    Field/FieldHeader.h \
    Field/RoutePlotter.h \
    Game/Game.h \
    Game/GameDestroyer.h \
    Game/GameFacade.h \
    Game/GameInfo.h \
    Game/GameMediator.h \
    Handler/RouteHandler.h \
    Handler/UnitActionHandler.h \
    Handler/UnitBaseAttackHandler.h \
    Handler/UnitBaseHandler.h \
    Handler/UnitLandscapeHandler.h \
    Handler/UnitUnitAttackHandler.h \
    Handler/UnitUnitHandler.h \
    Handler/UnitUnitUnionHandler.h \
    Landscape/Forest.h \
    Landscape/ForestHill.h \
    Landscape/Hill.h \
    Landscape/ILandscape.h \
    Landscape/Landscape.h \
    Landscape/LandscapeFactory.h \
    Landscape/LandscapeHeader.h \
    Landscape/LandscapeProxy.h \
    Landscape/Mountain.h \
    Landscape/Plain.h \
    Landscape/Water.h \
    Log/ILogger.h \
    Log/LogAdapter.h \
    Log/Logger.h \
    Log/LoggerProxy.h \
    Log/Time.h \
    Neutrals/NeutralContext.h \
    Neutrals/NeutralObject.h \
    Object/Object.h \
    Player/NeutralPlayer.h \
    Player/Player.h \
    Player/PlayerState.h \
    Rules/EliminationRule.h \
    Rules/Rule.h \
    Rules/SpeedRule.h \
    Trivia/Attributes.h \
    Trivia/Point.h \
    Trivia/Snapshot.h \
    UI/AttributeWidget.h \
    UI/BaseWidget.h \
    UI/LoggingWindow.h \
    UI/MainWindow.h \
    UI/ModifiedScene.h \
    UI/ModifiedView.h \
    UI/NewGameWindow.h \
    UI/PlayerWidget.h \
    UI/TurnButton.h \
    UI/VisualItem.h \
    UI/WinnerWindow.h \
    Unit/IUnit.h \
    Unit/Melee.h \
    Unit/Ranged.h \
    Unit/SiegeEngine.h \
    Unit/Unit.h \
    Unit/UnitFactory.h \
    Unit/UnitGroup.h \
    Unit/UnitHeader.h \

FORMS    += \
    UI/AttributeWidget.ui \
    UI/BaseWidget.ui \
    UI/LoggingWindow.ui \
    UI/MainWindow.ui \
    UI/NewGameWindow.ui \
    UI/PlayerWidget.ui \
    UI/TurnButton.ui \
    UI/WinnerWindow.ui

RESOURCES += \
    imgs.qrc

DISTFILES +=
