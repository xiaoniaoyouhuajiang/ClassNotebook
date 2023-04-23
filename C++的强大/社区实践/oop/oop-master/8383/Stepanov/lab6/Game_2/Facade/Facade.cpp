//
//  Facade.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 04.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Facade.hpp"

Facade::Facade (Field *f, Base *first, Base *second){
    field = f;
    this->first = first;
    this->second = second;
}

void Facade::printField (){
    
    for (int i = -1; i <= field->getHeight(); i++){
           
           for (int j = -1; j <= field->getWidth(); j++){

               if ((i == -1 && j == -1) || (i == -1 && j == field->getWidth()) ||
                   (i == field->getHeight() && j == -1) || (i == field->getHeight() && j == field->getWidth())){

                   std::cout << " ";

               } else if (i == -1 || i == field->getHeight()) {

                   std::cout << "--";

               } else if (j == -1 || j == field->getWidth()) {

                   std::cout << "|";

               } else {
                   
                   
                   switch (field->whatInCell(j, i)) {
                           case 1:
                           std::cout << field->getBase(j, i);
                               break;
                       case 2:
                           std::cout << field->getNeutralObject(j, i)->getName();
                           break;
                           
                           case 3:
                           std::cout << field->getUnit(j, i)->getName();
                               break;
                           
                           case 4:
                           std::cout << field->getLandscape(j, i)->getName();
                           std::cout << field->getLandscape(j, i)->getName();
                               break;

                               
                           default:
                               std::cout << "  ";
                               break;
                       
                       
                   
                       

                   }
               }
           }
           
           std::cout << std::endl;
       }
}


void Facade::printPoints () {
    for (int i = 0; i < 9; i++){
                
        Unit *firstUnit = first->getUnit(i);
        Unit *secondUnit = second->getUnit(i);

        if (!(firstUnit || secondUnit)) continue;

        if (firstUnit) { std::cout <<firstUnit->getName() <<
            "\th = " << firstUnit->health.getPoint() <<
            "\ta = " << firstUnit->armor.getPoint() <<
            "\tp = " << firstUnit->attack.getPoint() << "\t";

        } else {
            std::cout << "\t\t\t\t\t\t\t";
        }

        if (secondUnit) { std::cout <<secondUnit->getName() <<
            "\th = " << secondUnit->health.getPoint() <<
            "\ta = " << secondUnit->armor.getPoint() <<
            "\tp = " << secondUnit->attack.getPoint() << std::endl;

        } else {
            std::cout << std::endl;
        }
    }
}
