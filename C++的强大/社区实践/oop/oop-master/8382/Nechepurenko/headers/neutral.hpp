#pragma once
#include "unit.hpp"

class BuffInterface {
    public:
        virtual void buff(Unit* u) = 0;
};

class NeutralObject : public Object {
    public:
        ObjectType getType() {return c_type;}
        int getAmount() {return amount;}
        NeutralObject(ObjectType type, int amount) : Object(type), amount(amount){}
        ~NeutralObject() {}
    protected:
        int amount;

};

class HealBuff : public NeutralObject, public BuffInterface {
    public:
        HealBuff(int amount = 50)
        : NeutralObject(ObjectType::NEUTRAL_HEAL, amount) {} 
        void buff(Unit* u);
        ~HealBuff() {};
    
};

class ArmorBuff : public NeutralObject, public BuffInterface {
    public:
        ArmorBuff(int amount = 50)
        : NeutralObject(ObjectType::NEUTRAL_HEAL, amount) {} 
        void buff(Unit* u);
        ~ArmorBuff() {};
};

class DamageBuff : public NeutralObject, public BuffInterface {
    public:
        DamageBuff(int amount = 20)
        : NeutralObject(ObjectType::NEUTRAL_DAMAGE, amount) {} 
        void buff(Unit* u);
        ~DamageBuff() {};
};

class SpeedBuff : public NeutralObject, public BuffInterface {
    public:
        SpeedBuff(int amount = 2)
        : NeutralObject(ObjectType::NEUTRAL_SPEED, amount) {} 
        void buff(Unit* u);
        ~SpeedBuff() {};
};

Unit& operator+(Unit& u, HealBuff& buff);

Unit& operator*(Unit& u, DamageBuff& buff);

Unit& operator-(Unit& u, SpeedBuff& buff);

Unit& operator/(Unit& u, ArmorBuff& buff);