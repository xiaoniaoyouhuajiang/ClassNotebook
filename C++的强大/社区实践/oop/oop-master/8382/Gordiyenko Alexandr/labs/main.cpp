#include <iostream>
#include "Units/Unit.h"
#include "Field.h"
#include "extra1/UnitCreator.h"
#include "Units/Necromancer.h"
#include "Units/Priest.h"
#include "Units/Katanadude.h"
#include "Base.h"
#include "extra1/iterator.h"
#include "extra2/unitsgroup.h"
#include "GameFacade.h"
#include "Exceptions.h"
#include "extra6/Rules.h"
#include "extra2/Neutral/NeutralObject.h"
#include "extra3/facade.h"

void execGameRule(){ // Игра по одному из двух правил

//    //обратотка исключений
//    try {
//        GameFacade<Rule2>& facade = GameFacade<Rule2>::Instance(); //сиглтон
//        //GameFacade<Rule1> facade1 = GameFacade<Rule1>::Instance();
//        //GameFacade<Rule2> facade;
//        facade.createField();
//
//        std::cout << "Iterate throw field!" << std::endl;
//        Field* field = facade.getField();
//        Iterator iter1(field);
//        while (iter1.goNext()){
//            Cell* cell = *iter1;
//            std::cout << cell->y << " " << cell->x << " ";
//
//            if(cell->object!= nullptr) {
//                std::cout << "(" << cell->object->typeNeutral() << ", ";
//            }
//            else {
//                std::cout << " ";
//            }
//
//            if(cell->landscape!= nullptr) {
//                std::cout << cell->landscape->typeLandscape() << ")" << std::endl;
//            }
//            else {
//                std::cout << " ";
//            }
//        }
//        std::cout << std::endl;
//
//        facade.play();
//    }
//    catch(InputException e) {
//        std::cout << e.typeOfError() << std::endl;
//    }
//    catch(LogicException e) {
//        std::cout << e.typeOfError() << std::endl;
//    }

}

void execFacade(){ // Режим без правил, 1 игрок
    Facade *facade = new Facade();
    (*facade).createField();
    (*facade).play();
}


int main() {

    //execGameRule();
    execFacade();
    return 0;
}