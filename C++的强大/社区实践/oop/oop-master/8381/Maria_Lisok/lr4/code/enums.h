#ifndef ENUMS_H
#define ENUMS_H
#define FILENAME "log.txt"
enum Actions{
    GAME_INFO=1,
    BASE_INFO,
    LAND_INFO,
    NEUTRALS_INFO,
    UNITS_INFO,
    UNIT_ADD,
    BASE_ADD,
    NEUTRAL_ADD,
    MOVE,
    GETXPOS,
    ATTACK,
    UNIT_FIND,
    NEUTRAL_FIND,
    UNIT_INFO,
    NEUTRAL_INFO,
    LAND_CELL
};
enum UnitsType{
    ARCHER=20,
    SHAMAN,
    KNIGTH,
    RIDER,
    SWARDMAN,
    ORK,
    COMPOSITEUNITS
};
enum LandscapeType{
    FOREST=40,
    RIVER,
    MOUNTAIN
};
enum NeutralType{
    HELMET=60,
    MITTENS,
    SABATON,
    BANDAGE,
    POWERPOTION,
    COVID19,
    CODID37,
    SWORD,
    HATCHET
};
enum LogPlace{
    TOTERMINAL,
    TOFILE,
    NOLOG
};

#endif // ENUMS_H
