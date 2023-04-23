#ifndef INC_1_LAB_TEXTUREPROXY_H
#define INC_1_LAB_TEXTUREPROXY_H

#include "../Texture/Texture.h"
#include "../Point.h"

class TextureProxy {

 private:
  Texture *texture;

 public:
  TextureProxy(Texture *texture);

  int getDamageCoef(WeaponType type);
  int getAbsorptionCoef(ArmorType type);
};

#endif //INC_1_LAB_TEXTUREPROXY_H
