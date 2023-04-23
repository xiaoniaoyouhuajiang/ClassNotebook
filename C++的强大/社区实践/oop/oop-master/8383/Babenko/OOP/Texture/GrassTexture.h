#ifndef LAB2_OOP_GRASSTEXTURE_H
#define LAB2_OOP_GRASSTEXTURE_H

#include "../Texture/Texture.h"

class GrassTexture : public Texture {
 public:
  void print(std::ostream &stream, GameObject &object) const override {
    stream << "[" << object << "]";
  }

  void print(std::ostream &stream) const override {
    stream << "[" << "." << "]";
  }

  int getDamageCoef(WeaponType type) override {
    switch (type) {
      case WeaponType::MAGIC :return 1;
      case WeaponType::PHYSIC:return 4;
      case WeaponType::FAR:return 5;
    }
  }

  int getAbsorptionCoef(ArmorType type) override {
    switch (type) {
      case ArmorType::HEAVY:
      case ArmorType::LIGHT:
      case ArmorType::MEDIUM:
      case ArmorType::BASE:return 1;
    }
  }
};

#endif //LAB2_OOP_GRASSTEXTURE_H
