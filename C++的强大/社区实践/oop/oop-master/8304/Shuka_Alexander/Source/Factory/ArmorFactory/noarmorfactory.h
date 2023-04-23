#ifndef NOARMORFABRIC_H
#define NOARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/noarmor.h"


class NoArmorFactory : public ArmorFactory
{
public:
    virtual std::shared_ptr<Armor> createArmor() const override;
};

#endif // NOARMORFABRIC_H
