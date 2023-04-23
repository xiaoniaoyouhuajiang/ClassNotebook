#include "TextureProxy.h"

TextureProxy::TextureProxy(Texture *texture) : texture(texture) {}

int TextureProxy::getDamageCoef(WeaponType type) {
  if (texture) {
    return texture->getDamageCoef(type);
  } else {
    return 1;
  }
}

int TextureProxy::getAbsorptionCoef(ArmorType type) {
  if (texture) {
    return texture->getAbsorptionCoef(type);
  } else {
    return 1;
  }
}