TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -LC:\SFML\lib
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:\SFML\include
DEPENDPATH += C:\SFML\include

SOURCES += \
        Armor.cpp \
        AttackCommand.cpp \
        Base.cpp \
        BaseCommand.cpp \
        BaseConstructor.cpp \
        ChaosBase.cpp \
        ChaosFactory.cpp \
        ClickedCommand.cpp \
        CreateBaseCommand.cpp \
        FieldCommand.cpp \
        Game.cpp \
        GameFacade.cpp \
        GameObj.cpp \
        Gamefield.cpp \
        GoblinCatapult.cpp \
        Grass.cpp \
        GrassProxy.cpp \
        GrassTexture.cpp \
        Gretchin.cpp \
        Healing.cpp \
        HumanBase.cpp \
        HumanCleric.cpp \
        HumanFactory.cpp \
        HumanGuard.cpp \
        HumanTrebuchet.cpp \
        INeutralObj.cpp \
        Mediator.cpp \
        Mine.cpp \
        MoveCommand.cpp \
        Observer.cpp \
        Portal.cpp \
        PublicObj.cpp \
        River.cpp \
        RiverProxy.cpp \
        RiverTexture.cpp \
        Stone.cpp \
        StoneProxy.cpp \
        StoneTexture.cpp \
        TBattleCharacter.cpp \
        TMagicCharacter.cpp \
        TSiegeCharacter.cpp \
        Terrain.cpp \
        TerrainProxy.cpp \
        TerrainTexture.cpp \
        TrolsMagic.cpp \
        Unit.cpp \
        UnitInfoCommand.cpp \
        main.cpp

HEADERS += \
    AFactory.h \
    Armor.h \
    AttackCommand.h \
    Base.h \
    BaseCommand.h \
    BaseConstructor.h \
    ChaosBase.h \
    ChaosFactory.h \
    ClickedCommand.h \
    Command.h \
    CreateBaseCommand.h \
    Event.h \
    FieldCommand.h \
    Game.h \
    GameFacade.h \
    GameObj.h \
    Gamefield.h \
    GoblinCatapult.h \
    Grass.h \
    GrassProxy.h \
    GrassTexture.h \
    Gretchin.h \
    Healing.h \
    HumanBase.h \
    HumanCleric.h \
    HumanFactory.h \
    HumanGuard.h \
    HumanTrebuchet.h \
    INeutralObj.h \
    ITerrain.h \
    Mediator.h \
    Mine.h \
    MoveCommand.h \
    Observer.h \
    Portal.h \
    PublicObj.h \
    River.h \
    RiverProxy.h \
    RiverTexture.h \
    Stone.h \
    StoneProxy.h \
    StoneTexture.h \
    TBattleCharacter.h \
    TMagicCharacter.h \
    TSiegeCharacter.h \
    Terrain.h \
    TerrainProxy.h \
    TerrainTexture.h \
    TrolsMagic.h \
    Unit.h \
    UnitInfoCommand.h \
    globalconst.h \
    stdlibrary.h
