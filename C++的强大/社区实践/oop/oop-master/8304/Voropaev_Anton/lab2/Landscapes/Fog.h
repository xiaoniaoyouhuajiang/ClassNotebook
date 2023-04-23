#ifndef OOP_FOG_H
#define OOP_FOG_H

#include "Landscape.h"

class Fog : public Landscape, public Location {
public:
    Fog() = default;
    ~Fog() = default;
    LandscapeInfo interaction(LandscapeTypes type) final;
};


#endif //OOP_FOG_H
