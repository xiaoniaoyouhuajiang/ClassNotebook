#ifndef LAB2_MEDIATOR_H
#define LAB2_MEDIATOR_H


#include "Base.h"
#include "Unit.h"
#include "NeutralObject.h"
#include "Landscape.h"
#include "BaseMediator.h"

class Mediator : public BaseMediator {
private:
    std::shared_ptr<BaseComponent> elem1 = nullptr;
    std::shared_ptr<BaseComponent> elem2 = nullptr;
    BaseComponent* base = nullptr;
    std::string command;

public:
    Mediator(std::shared_ptr<Unit>& c1, std::shared_ptr<NeutralObject>& c2) : elem1(c1), elem2(c2) {
        elem1->set_mediator(this);
        elem2->set_mediator(this);
    }

    Mediator(std::shared_ptr<Unit>& c1, std::shared_ptr<Landscape>& c2) : elem1(c1), elem2(c2) {
        elem1->set_mediator(this);
        elem2->set_mediator(this);
    }

    Mediator(std::shared_ptr<Unit>& c1, std::shared_ptr<Unit>& c2) : elem1(c1), elem2(c2) {
        elem1->set_mediator(this);
        elem2->set_mediator(this);
        command = "unit action";
    }

    Mediator(Base* base, std::shared_ptr<Unit>& c2) : base(base), elem2(c2) {
        this->base->set_mediator(this);
        elem2->set_mediator(this);
        command = "base action";
    }

    void make_action() const override;
};


#endif
