#ifndef LAB2_NEUTRALOBJECT_H
#define LAB2_NEUTRALOBJECT_H


#include <HealthPoints.h>
#include <Attack.h>
#include "BaseComponent.h"

class NeutralObject : public BaseComponent {
public:
    NeutralObject(int def, int att, int intell) : BaseComponent(def, att, intell) {}

    void interaction() const override;
};


#endif
