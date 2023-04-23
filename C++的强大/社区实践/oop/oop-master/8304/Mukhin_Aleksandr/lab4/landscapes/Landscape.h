#ifndef LAB2_LANDSCAPE_H
#define LAB2_LANDSCAPE_H

#include "HealthPoints.h"
#include "Attack.h"
#include "BaseComponent.h"

class Landscape : public BaseComponent {
public:
    Landscape() = default;
    Landscape(int def, int att, int intell, bool stand) : BaseComponent(def, att, stand), can_stand(stand) {}
    void interaction() const override;
    bool can_stand{};
};


#endif
