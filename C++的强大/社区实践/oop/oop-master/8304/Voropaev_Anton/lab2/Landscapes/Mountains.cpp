#include "Mountains.h"

LandscapeInfo Mountains::interaction(LandscapeTypes type) {
    std::vector<char> units = {'m', 'n'};
    return {units, 5, EffectTypes::Range };
}
