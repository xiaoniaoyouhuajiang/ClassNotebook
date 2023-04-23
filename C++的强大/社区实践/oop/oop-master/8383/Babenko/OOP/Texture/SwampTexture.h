#ifndef LAB2_OOP_WATERTEXTURE_H
#define LAB2_OOP_WATERTEXTURE_H

#include "../Texture/Texture.h"

class SwampTexture : public Texture {
 public:
  void print(std::ostream &stream, GameObject &object) const override {
    stream << "{" << object << "}";
  }

  void print(std::ostream &stream) const override {
    stream << "{" << "." << "}";
  }

  int getDamageCoef(WeaponType type) override {
    switch (type) {
      case WeaponType::PHYSIC :return 1;
      case WeaponType::MAGIC:
      case WeaponType::FAR:return 4;
    }
  }

  int getAbsorptionCoef(ArmorType type) override {
    switch (type) {
      case ArmorType::HEAVY:return 1;
      case ArmorType::LIGHT:return 3;
      case ArmorType::MEDIUM:return 2;
      case ArmorType::BASE:return 1;
    }
  }
};

#endif //LAB2_OOP_WATERTEXTURE_H
