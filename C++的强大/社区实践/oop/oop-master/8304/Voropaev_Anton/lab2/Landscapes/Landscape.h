#ifndef OOP_LANDSCAPE_H
#define OOP_LANDSCAPE_H

#include <vector>
#include "../Object.h"
#include "../Unit Attributes/Location.h"

enum class LandscapeTypes : int{
    Mountain, Desert, Fog, None
};

enum class EffectTypes {
    Damage, Health, Range
};

struct LandscapeInfo {
    std::vector<char> effected_units;
    int effect_num = 0;
    EffectTypes type;
};

class Landscape {
public:
    Landscape() = default;
    ~Landscape() = default;
    virtual LandscapeInfo interaction(LandscapeTypes type) = 0;
};

#endif //OOP_LANDSCAPE_H
