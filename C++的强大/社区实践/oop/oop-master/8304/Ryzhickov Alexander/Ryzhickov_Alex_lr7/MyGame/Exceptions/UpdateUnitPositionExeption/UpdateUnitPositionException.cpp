//
// Created by Alex on 21.05.2020.
//

#include <iostream>
#include "UpdateUnitPositionException.h"

namespace MyGameException {
    UpdateUnitPositionException::UpdateUnitPositionException(int x, int y, int fieldWidth, int fieldHeight, int code)
            : x(x), y(y),
              fieldWidth(
                      fieldWidth),
              fieldHeight(
                      fieldHeight),
              code(code) {}

    std::string UpdateUnitPositionException::what() {
        std::string string;
        if (code == 1) {
            string += "UpdateUnitPositionException. NewPointPosition outside the field boundaries\n";
            string +=
                    "Width [0:" + std::to_string(fieldWidth) + "] Height [0:" + std::to_string(fieldHeight) + "]     ";
            string += "NewPositionPoint for unit x:" + std::to_string(x) + " y:" + std::to_string(y) + "\n";
        }
        if (code == 2) {
            string += "UpdateUnitPositionException. LastPointPosition outside the field boundaries\n";
            string +=
                    "Width [0:" + std::to_string(fieldWidth) + "] Height [0:" + std::to_string(fieldHeight) + "]     ";
            string += "LastPositionPoint for unit x:" + std::to_string(x) + " y:" + std::to_string(y) + "\n";
        }
        return string;
    }
}