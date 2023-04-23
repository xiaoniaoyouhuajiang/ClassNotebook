#ifndef LAB2_UNIT_H
#define LAB2_UNIT_H

#include "Creator.h"
#include "HealthPoints.h"
#include "Attack.h"
#include <string>
#include "BaseComponent.h"

class Unit : public BaseComponent {
private:
    friend std::ostream& operator<<(std::ostream&, const Unit&);
public:
    int x = -1;
    int y = -1;
    Unit() = default;
    Unit(int def, int att, int intell) : BaseComponent(def, att, intell) {}

    std::string unit_symbol{};
    void interaction() const override;
    virtual void greeting() const = 0;
    virtual ~Unit() {};
};


#endif
