#pragma once
#include "objects/object.h"
#include "field/cell.h"
//#include "observer/iobserver.h"
#include "objects/object.h"

constexpr int LIGHT_RADIUS = 1;
constexpr int MEDIUM_RADIUS = 2;
constexpr int HEAVY_RADIUS = 3;
constexpr int DAMAGE = 1;


class Unit : /*virtual*/ public Object, virtual IPublisher    //leaf
{
private:
    std::list<IObserver*> _observers;

public:
    Unit();
    virtual ~Unit();
    int damage;
    int movementRadius;
    int attackRadius;

    bool shieldUsed = false;
    bool shieldEnabled;
    int MoveRadiusBetter;
    int AttackRadiusBetter;
    
    int numBase;

    bool isArcher = false;
    bool isCrossBowMan = false;
    bool isKnight = false;
    bool isSpearMan = false;
    bool isHeavyRider = false;
    bool isLightRider = false;

    bool canMove(int x, int y) override;

    // Object* observingObject;

    void attachObserver(IObserver *observer) override;
    void detachObserver(IObserver *observer) override;
    void notify(std::string message) override;
    
};
