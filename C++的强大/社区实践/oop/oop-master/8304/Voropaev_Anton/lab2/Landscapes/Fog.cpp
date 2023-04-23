#include "Fog.h"

LandscapeInfo Fog::interaction(LandscapeTypes type) {
    std::vector<char> units = {'w', 's', 'n', 'm', 'c', 'p'};
    return {units, -15, EffectTypes::Damage};
}
