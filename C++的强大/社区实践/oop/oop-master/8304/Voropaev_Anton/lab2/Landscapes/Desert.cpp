#include "Desert.h"

LandscapeInfo Desert::interaction(LandscapeTypes type) {
    std::vector<char> units = {'w', 's', 'c', 'p'};
    return {units, -60, EffectTypes ::Health};
}
