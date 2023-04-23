#include "Thing.hpp"

Unit &operator<<(Unit &unit, const Thing &thing) {
    thing.applyTo(unit);
    return unit;
}