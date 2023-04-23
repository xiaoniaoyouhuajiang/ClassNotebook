#ifndef LAB2_BASECOMPONENT_H
#define LAB2_BASECOMPONENT_H

#include "HealthPoints.h"
#include "Attack.h"
#include <memory>
#include "BaseMediator.h"

class BaseMediator;
class BaseComponent {
protected:
    BaseMediator* mediator = nullptr;
    Attack attack;
    HealthPoints defense;
    int intelligence;

public:
    BaseComponent(int def, int att, int intell) : defense(def), attack(att), intelligence(intell) {}
    BaseComponent() = default;
    BaseComponent(BaseMediator* med) : mediator(med) {}

    void set_mediator(BaseMediator*);
    [[nodiscard]] int get_health() const;
    [[nodiscard]] int get_attack() const;
    [[nodiscard]] int get_intelligence() const;
    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;

    void change_health(int);
    void change_attack(int);
    void change_intelligence(int);

    virtual void interaction() const = 0;
};


#endif
