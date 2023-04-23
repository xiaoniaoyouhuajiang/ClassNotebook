#ifndef LAB2_BASE_H
#define LAB2_BASE_H
#include <memory>
#include <vector>
#include <iostream>
#include "Unit.h"

class Base : public BaseComponent {
    int max_size = 0;
    std::vector<std::shared_ptr<Unit>> units;
    friend class Boardfield;
    int y = -1;
    int x = -1;
public:
    Base() = default;
    Base(int size) : BaseComponent(100, 50, 50), max_size(size) {}

    void add_unit(std::shared_ptr<Unit>&);
    void get_base();
    int current_size = 0;
    void interaction() const override;
};


#endif
