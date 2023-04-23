#ifndef LAB2_BASE_H
#define LAB2_BASE_H
#include <memory>
#include <vector>
#include <iostream>
#include "AbstractionBase.h"
#include "Unit.h"

class Base : public BaseComponent, public AbstractionBase {
    int max_size = 0;
    std::vector<std::shared_ptr<Unit>> units;
    friend class Boardfield;
    friend std::ostream& operator<<(std::ostream&, const Base&);

public:
    Base() = default;
    Base(int size) : BaseComponent(100, 50, 50), max_size(size) {}

    void add_unit(std::shared_ptr<Unit>&) override;
    void get_base() override;
    int current_size = 0;
    void interaction() const override;
};


#endif
