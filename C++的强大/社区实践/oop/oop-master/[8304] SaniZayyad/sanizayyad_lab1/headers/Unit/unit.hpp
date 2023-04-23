#ifndef unit_hpp
#define unit_hpp

#include "movingInterface.hpp"
#include "mediator.hpp"

#include "armor.hpp"
#include "weapon.hpp"

#include <stdio.h>
#include <memory>

constexpr double SHORT_RANGE_HEALTHPOINTS = 100;
constexpr double ARCHER_HEALTHPOINTS = 110;
constexpr double BALLISTICS_HEALTHPOINTS = 150;
constexpr double VAMPIRE_HEALTHPOINTS = 180;
constexpr double DRAGON_HEALTHPOINTS = 200;


class Unit: public MovingInterface, public std::enable_shared_from_this<Unit>{
    public:
        explicit Unit(const Position2D& position, std::shared_ptr<Mediator> mediator);
        virtual ~Unit() = default;

        Unit(const Unit& unit);
    
        const Position2D& getPosition() const;
        int getHealthPoints() const;
        std::string getUnitName() const;
        const std::unique_ptr<Armor>& getArmor() const;
        const std::unique_ptr<Weapon>& getWeapon() const;

        void setWeapon(std::unique_ptr<Weapon> weapon);
        void setArmor(std::unique_ptr<Armor> armor);
        void makeDamage(int damage);
        void getUnitInfo();

    
        virtual std::shared_ptr<Unit> clone() = 0;  //prototype pattern

    protected:
        void doCopy(const Unit& unit);

    protected:
        Position2D position;
        int healthPoints;
        std::string unitName;
        std::unique_ptr<Armor> armor;
        std::unique_ptr<Weapon> weapon;
        std::shared_ptr<Mediator> mediator;
    };
 
#endif /* unit_hpp */
