#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H


#include "globalconst.h"

class TerrainTexture
{
protected:

    int character;
public:
    int getTexture() ;
    TerrainTexture();
    virtual ~TerrainTexture();
};




#endif // TERRAINTEXTURE_H


