#pragma once

#include <algorithm>

class Attribute {
protected:
    unsigned value;
    unsigned max_value;

public:
    Attribute() {
        value = 0;
        max_value = 0;
    };
    Attribute(unsigned value, unsigned max_value)
        : value(value), max_value(max_value){};

    unsigned get_value() { return value; };
    unsigned get_max_value() { return max_value; };
    void increase(unsigned amount) {
        value = std::min(value + amount, max_value);
    };
    void decrease(unsigned amount) {
        value = (value <= amount) ? 0 : value - amount;
    };
};
