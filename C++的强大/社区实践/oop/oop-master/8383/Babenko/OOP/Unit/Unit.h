#ifndef OOP_LAB1_UNIT_H
#define OOP_LAB1_UNIT_H

#include "../Armor/Armor.h"
#include "../Weapon/Weapon.h"
#include "../Point.h"
#include "../GameObject.h"
#include "../Observers/UnitObserver.h"
#include "../Proxy/TextureProxy.h"
#include "../NeutralObject/NeutralObject.h"
#include "../FlyWeight/WeaponFlyWeight.h"
#include "../FlyWeight/ArmorFlyWeight.h"

#include <vector>
#include <ostream>
#include <unordered_map>

enum class UnitType {
  VIKING,
  WIZARD,
  ARCHER,
  UNKNOWN
};

class UnitObserver;

class Unit : public GameObject {
 protected:
  std::vector<UnitObserver *> unitObservers;
  UnitType unitType;

  Armor &unitArmor;
  Weapon &unitWeapon;
  int unitHealth;
  void print(std::ostream &stream) const override;

  static inline std::unordered_map<std::string, UnitType> const unitTypeMap = {
      {"VIKING", UnitType::VIKING},
      {"WIZARD", UnitType::WIZARD},
      {"ARCHER", UnitType::ARCHER}
  };

 public:

  Unit(const Unit &other);
  Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health);

  Weapon &getUnitWeapon() {
    return unitWeapon;
  }
  Armor &getUnitArmor() {
    return unitArmor;
  }
  UnitType getUnitType() {
    return unitType;
  }
  int getUnitHealth();

  void move(Point position);
  void attack(Unit &other);
  void damage(int damage);
  void heal(int hp);

  void addObserver(UnitObserver *observer);

  Unit &operator=(const Unit &other);
  Unit &operator<<(NeutralObject *neutralObject);

  static inline UnitType getUnitTypeFromString(std::string &string) {
    auto iterator = unitTypeMap.find(string);
    if (iterator != unitTypeMap.end()) {
      return iterator -> second;
    }

    return UnitType::UNKNOWN;
  }

  static inline std::string getRawUnitType(const UnitType &type) {
    switch (type) {
      case UnitType::WIZARD:return "WIZARD";
      case UnitType::ARCHER:return "ARCHER";
      case UnitType::VIKING:return "VIKING";
      case UnitType ::UNKNOWN:return "";
    }
  }

  friend LogProxy& operator<<(LogProxy &logger, Unit &unit){
    logger << "Unit( x: " << unit.objectPosition.x << " y: " << unit.objectPosition.y << " health: " << unit.unitHealth << ")";
    return logger;
  }

  ~Unit();
};

#endif //OOP_LAB1_UNIT_H