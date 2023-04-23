#ifndef OOP_DESERT_H
#define OOP_DESERT_H
#include "Landscape.h"
class Desert : public Landscape, public Location {
public:
    Desert() = default;
    ~Desert() = default;
    LandscapeInfo interaction(LandscapeTypes type) final;
};


#endif //OOP_DESERT_H
