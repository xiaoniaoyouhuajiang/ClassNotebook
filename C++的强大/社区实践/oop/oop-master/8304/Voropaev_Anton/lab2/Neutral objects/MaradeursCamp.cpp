#include "MaradeursCamp.h"

MaradeursCamp::MaradeursCamp(int x, int y) {
    this->setPosition(x, y);
}

int MaradeursCamp::operator()(Unit *unit) {
    strategy.change_attribute(unit, -150);
    return 0;
}
