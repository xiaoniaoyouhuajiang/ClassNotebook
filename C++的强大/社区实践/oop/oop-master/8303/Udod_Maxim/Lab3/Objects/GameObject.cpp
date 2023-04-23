//
// Created by shenk on 01.03.2020.
//

#include "GameObject.h"

std::ostream &operator<<(std::ostream &stream, const GameObject &object){

    object.print(stream);

}