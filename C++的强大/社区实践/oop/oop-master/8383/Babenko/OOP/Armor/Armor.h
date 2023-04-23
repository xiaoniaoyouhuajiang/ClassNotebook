#ifndef OOP_LAB1_ARMOR_H
#define OOP_LAB1_ARMOR_H

#include <ostream>

enum class ArmorType {
  HEAVY,
  MEDIUM,
  LIGHT,
  BASE
};

class Armor {

 protected:
  ArmorType type;
  int damageResistance;

 public:
  Armor() {}
  int getDamageResistance() const {
    return damageResistance;
  }
  ArmorType getArmorType() {
    return type;
  }

  bool operator==(Armor &other) {
    return type == other.type && damageResistance == other.damageResistance;
  }

  Armor &operator=(const Armor &other) {

    if (this == &other)
      return *this;
    type = other.type;
    damageResistance = other.damageResistance;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Armor &armor){

    stream << "Armor( " << "Damage Resistance: " << armor.damageResistance << " )";
    return stream;
  }

};

#endif //OOP_LAB1_ARMOR_H