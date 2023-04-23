#ifndef LAB2_BASECOMPONENT_H
#define LAB2_BASECOMPONENT_H

#include "HealthPoints.h"
#include "Attack.h"
#include <memory>
#include "BaseMediator.h"

class BaseMediator;
class BaseComponent {
private:
    friend std::ostream& operator<<(std::ostream&, const BaseComponent&);
protected:
    BaseMediator* mediator = nullptr;
    Attack attack;
    HealthPoints defense;
    int intelligence;

public:
    int type = 0;
    BaseComponent(int def, int att, int intell) : defense(def), attack(att), intelligence(intell) {}
    BaseComponent() = default;
    BaseComponent(BaseMediator* med) : mediator(med) {}
    void set_params(int, int, int);
    void set_mediator(BaseMediator*);
    [[nodiscard]] int get_health() const;
    [[nodiscard]] int get_attack() const;
    [[nodiscard]] int get_intelligence() const;

    void change_health(int);
    void change_attack(int);
    void change_intelligence(int);

    void set_health(int);
    void set_attack(int);
    void set_intelligence(int);

    virtual void interaction() const = 0;
};


#endif
