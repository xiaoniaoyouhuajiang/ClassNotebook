
#include "TrainingCamp.h"

TrainingCamp::TrainingCamp(int x, int y) {
    this->setPosition(x, y);
    t_camp = new TrainingCamp;
}


int TrainingCamp::operator()(Unit *unit) {
    strategy.change_attribute(unit, 15);
    return 0;
}
