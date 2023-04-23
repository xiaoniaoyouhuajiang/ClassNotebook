#pragma once

enum Action { ATTACK, MOVE, ADD_BASE, ADD_UNIT, NEW_GAME, SAVE_GAME, LOAD_GAME };

enum CreatureType { BASE, UNIT };

enum NeutralObjectType { FORGE, TEMPLE, BANNER, TOWER };

enum UnitType { ABSORB_INFANTRY, ABSORB_CAVALRY, ABSORB_ARCHER,
                CRIT_INFANTRY, CRIT_CAVALRY, CRIT_ARCHER };

enum LandscapeType {MOUNTAINS, WATER, GROUND};

enum LogEventType{
    NEW_GAME_STARTED,

    CREATED_BASE,
    CREATED_UNIT,

    UNIT_MOVED,
    ATTACK_COMMITED,
};

enum LogFormatType {
    ACTIONS_ONLY,
    FULL_INFO
};

enum UPDATE_UI_TYPE{
    TOTAL_UPDATE,
    PARTICAL_UPDATE
};

enum RuleType {
    FIRST,
    SECOND
};

enum PlayersOrder{
    USUAL,
    REVERSIVE
};
