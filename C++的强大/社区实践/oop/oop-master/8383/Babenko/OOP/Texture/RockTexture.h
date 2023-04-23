#ifndef LAB2_OOP_ROCKTEXTURE_H
#define LAB2_OOP_ROCKTEXTURE_H

#include "../Texture/Texture.h"

class RockTexture : public Texture {
 public:
  void print(std::ostream &stream, GameObject &object) const override {
    stream << "^" << object << "^";
  }

  void print(std::ostream &stream) const override {
    stream << "^" << "." << "^";
  }

  int getDamageCoef(WeaponType type) override {
    switch (type) {
      case WeaponType::PHYSIC :return 1;
      case WeaponType::MAGIC:
      case WeaponType::FAR:return 3;
    }
  }

  int getAbsorptionCoef(ArmorType type) override {
    switch (type) {
      case ArmorType::MEDIUM:return 2;
      case ArmorType::LIGHT:return 5;
      case ArmorType::HEAVY:
      case ArmorType::BASE:return 1;
    }
  }
};

#endif //LAB2_OOP_ROCKTEXTURE_H
