#ifndef unit_hpp
#define unit_hpp

#include "movingInterface.hpp"
#include "mediator.hpp"
#include "subject.hpp"

#include "armor.hpp"
#include "weapon.hpp"

#include <stdio.h>
#include <memory>

constexpr double SHORT_RANGE_HEALTHPOINTS = 100;
constexpr double ARCHER_HEALTHPOINTS = 100;
constexpr double BALLISTICS_HEALTHPOINTS = 150;
constexpr double VAMPIRE_HEALTHPOINTS = 180;
constexpr double DRAGON_HEALTHPOINTS = 200;

namespace unit {

enum class PLAYER: int {
    ONE,
    TWO
};

class Unit: public MovingInterface, public ObserverSubject{
    friend class UnitBuilder;
    public:
        explicit Unit(const Position2D& position, std::shared_ptr<Mediator> mediator);
        virtual ~Unit() = default;

        Unit(const Unit& unit);
    
        const Position2D& getPosition() const;
        double getHealthPoints() const;
        std::string getUnitName() const;
        const std::shared_ptr<Armor>& getArmor() const;
        const std::shared_ptr<Weapon>& getWeapon() const;
        PLAYER getPlayer() const;


        void setWeapon(std::shared_ptr<Weapon> weapon);
        void setArmor(std::shared_ptr<Armor> armor);
        void makeDamage(double damage);
        void getUnitInfo();
        void setPlayer(PLAYER player);

    
        virtual std::shared_ptr<Unit> clone() = 0;  //prototype pattern

    protected:
        void doCopy(const Unit& unit);

    protected:
        PLAYER player;
        Position2D position;
        double healthPoints;
        std::string unitName;
        std::shared_ptr<Armor> armor;
        std::shared_ptr<Weapon> weapon;
        std::shared_ptr<Mediator> mediator;
    };
 }
#endif /* unit_hpp */
