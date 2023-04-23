#ifndef LAB2_OOP_TEXTURE_H
#define LAB2_OOP_TEXTURE_H

#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../GameObject.h"

class Texture {
 public:
  virtual void print(std::ostream &stream, GameObject &object) const = 0;
  virtual void print(std::ostream &stream) const = 0;

  virtual int getDamageCoef(WeaponType type) = 0;
  virtual int getAbsorptionCoef(ArmorType type) = 0;

  friend std::ostream &operator<<(std::ostream &stream, const Texture &texture) {
    texture.print(stream);
    return stream;
  }
};

#endif //LAB2_OOP_TEXTURE_H
