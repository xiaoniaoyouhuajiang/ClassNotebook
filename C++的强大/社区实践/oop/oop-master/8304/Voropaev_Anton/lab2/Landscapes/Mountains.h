#ifndef OOP_MOUNTAINS_H
#define OOP_MOUNTAINS_H

#include "Landscape.h"

class Mountains : public Landscape, public Location {
public:
    Mountains() = default;
    ~Mountains() = default;
    LandscapeInfo interaction(LandscapeTypes type) final;
};


#endif //OOP_MOUNTAINS_H
