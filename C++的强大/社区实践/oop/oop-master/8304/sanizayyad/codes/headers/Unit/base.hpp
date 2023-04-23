#ifndef base_hpp
#define base_hpp

#include "unit.hpp"
#include "unitcreator.hpp"
#include "observerInterface.hpp"

#include <time.h>
#include <stdio.h>


class UnitStateSnap;


namespace unit {

constexpr int MAX_NUMBER_UNITS = 10;


class Base : public Unit, public ObserverInterface, public std::enable_shared_from_this<Base>
{
    friend class Snapshot;
public:
    explicit Base(const Position2D& position,std::shared_ptr<Mediator> mediator, PLAYER player,double healthPoints = 300);

    virtual bool moveLeft() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
    virtual bool moveRight() override;

    std::shared_ptr<Unit> createShortRangeUnit(int dx, int dy);
    std::shared_ptr<Unit> createLongRangeUnit(int dx, int dy);
    std::shared_ptr<Unit> createDynamicRangeUnit(int dx, int dy);
    
    std::shared_ptr<Unit> createUnitFromSnaphot(const UnitStateSnap& unitStateSnap);

    void baseInfo();
    size_t getNumberOfUnits() const;
    virtual void update() override;
    virtual std::shared_ptr<Unit> clone() override;
    
private:
    int generateRandomNum(int end) const;
    std::shared_ptr<Unit> createUnit(std::shared_ptr<Unit> unit);
    void setHealthPoints(double healthPoints);

private:
    UnitCreator creator;
    size_t numberOfUnits;
};


}




#endif /* base_hpp */
