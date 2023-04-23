
#ifndef UNTITLED13_OCEAN_H
#define UNTITLED13_OCEAN_H

#include "Landscape.h"

class Ocean: public Landscape {

public:

    void print(std::ostream &stream, GameObject &object) const override{

        stream << "{" << object << "}";

    }

    void print(std::ostream &stream) const override{

        stream << "{" << "." << "}";

    }

    int getDamageFactor(WeaponType type) override {

        switch (type){

            case WeaponType::PHYSIC :
            case WeaponType::FIREARMS:
                return 1;
            case WeaponType::MAGIC:
            case WeaponType::FAR:
                return 4;
        }

    }

    int getAbsorptionFactor(ArmorType type) override {
        switch (type){

            case ArmorType::MAGIC:
                return 2;
            case ArmorType::HEAVY:
                return 1;
            case ArmorType::LIGHT:
                return 3;
            case ArmorType::MEDIUM:
                return 2;
        }
    }

};


#endif //UNTITLED13_OCEAN_H
