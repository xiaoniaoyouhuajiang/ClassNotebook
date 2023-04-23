//
// Created by Alex on 08.03.2020.
//

#include "FieldLandscape.h"

FieldLandscape::FieldLandscape() {
    FieldLandscape::landscape= kindLandscape ::field;
}

bool FieldLandscape::getInformationAboutLandscape() {
    return true;
}

int FieldLandscape::getBonus(kindUnit kindUnit) {
    if(kindUnit==kindUnit::LightCavalry || kindUnit==kindUnit::HeavyCavalry){
        return 30;
    } else{
        return 0;
    }
}
