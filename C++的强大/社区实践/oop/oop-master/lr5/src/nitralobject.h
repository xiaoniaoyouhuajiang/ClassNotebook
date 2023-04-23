#include "unit.h"
#ifndef NITRALOBJECT_H
#define NITRALOBJECT_H



/* взаимодействие с нейтральными объектами с помощью паттерна "Стратегия" */

class NitralObject{
public:
    char sym;
    class Interaction{
    public:
        virtual bool compress(Unit* unit) = 0;
    };
    class Compressor{
        Interaction* inter;
    public:
        Compressor(Interaction* in) : inter(in){}
        bool compress(Unit* unit);
    };
    Compressor* comp = nullptr;
    NitralObject(){}
    virtual bool strategy(Unit* unit) = 0;
};

class Stone: public NitralObject{
public:
    Stone();
    class WarriorsInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class MagesInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class SaboteursInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    bool strategy(Unit* unit);
};

class Gold: public NitralObject{
public:
    Gold();
    class WarriorsInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class MagesInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class SaboteursInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    bool strategy(Unit* unit);
};

class ForceWell: public NitralObject{
public:
    ForceWell();
    class WarriorsInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class MagesInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class SaboteursInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    bool strategy(Unit* unit);
};

class LifeWell: public NitralObject{
public:
    LifeWell();
    class WarriorsInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class MagesInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    class SaboteursInteraction : public Interaction{
        bool compress(Unit *unit);
    };
    bool strategy(Unit* unit);
};


#endif // NITRALOBJECT_H
