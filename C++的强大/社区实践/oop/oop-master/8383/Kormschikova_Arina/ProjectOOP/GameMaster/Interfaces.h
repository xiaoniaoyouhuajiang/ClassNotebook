
#ifndef Header_h
#define Header_h

class GameMap;
class Unit;
class Base;
class NeutralObject;


class IUnits{
public:
    virtual void move(int x, int y, GameMap& map) {};
    virtual void showStat() {};
    virtual void getDamage(int damage) {};
    virtual void death() {};
   
};


class IObserver{
public:
    virtual void update() {};
};




class IGameBlock{
public:
    virtual bool setUnit(Unit* unit) = 0;
    virtual bool setBase(Base* base) = 0;
    virtual bool setObject(NeutralObject* obj) = 0;
    virtual bool deleteUnit() = 0;
    virtual bool isEmpty() = 0;
};


class IBase{
public:
    virtual bool createUnit() = 0;
    virtual bool createUnit(char type) = 0;
    virtual Unit* getUnit() = 0;
    virtual void showStat() {};
    virtual void updateU() {};
    
};


class INeutralObject{
public:
    virtual void action(Unit& unit) {};
    virtual void getDamage(int damage){};
};

class ILandscape{
    
};
#endif /* Header_h */
