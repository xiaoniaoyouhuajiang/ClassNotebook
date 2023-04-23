#ifndef EVENT_H
#define EVENT_H
class Base;
/*make namespace ev */

class Event{
  public:
   /* some events */

    enum UnitType{
      WARRIOR,
      MAGIC,
      SIEGE
    };

    enum RaceType{
        HUMANITY,
        CHAOS
    };

    enum HeroState{
        BLOCK_ATTACK,
        BLOCK_MOVEABLE,
        POISONED,
        NORMAL
       /* ... */
    };

    struct ClickedEvent{
        int x;
        int y;
    };

    enum Relation{
        ENEMY,
        FRIEND,
        NEUTRAL
    };

    struct AttackAttribute{
        int distant;
        int damage;
        int bonus;
        bool negativeEffect;
    };

    /* + something else*/
    struct MoveEvent{
        unsigned x;
        unsigned y;
    };

    struct BaseInfoEvent{
        int hitPoint;
        int unitCount;
        int unitLimit;
        int canCreate;
        RaceType race;
        Relation relation;
    };

    struct AttackEvent{
        int x;
        int y;
    };

    struct UnitInfoEvent{
        int hitPoint;
        int armor;
        int actionPoint;
        int damagePoint;
        int distantAttack;
        HeroState state_;
        Relation relation;
        UnitType unitType;
        RaceType rase;
    };


    struct BaseCreateEvent{
        int x;
        int y;
    };

    enum EventType{
       UNIT_DIE,
       UNIT_CREATE,
       HBASE_CREATE,
       CHBASE_CREATE,
       UNIT_ACTION,
       BASE_INFO,
       UNIT_INFO,
       ATTACK_ATTRIBUTE,
       CLICKED,
       MOVE,
       ATTACK,
       ERROR
       /* .... */
    };

    EventType type;

    union{
      UnitType unitType;
      UnitInfoEvent unitInfo;
      BaseInfoEvent baseInfo;
      AttackEvent attackCoord;
      BaseCreateEvent base;
      AttackAttribute attackAttribute;
      MoveEvent coord;
      ClickedEvent clicked;
      /* ... */
    };

};

#endif // EVENT_H
