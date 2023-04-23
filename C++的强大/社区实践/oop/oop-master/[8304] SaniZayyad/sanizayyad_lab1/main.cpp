#include <iostream>
#include <memory>
#include <vector>

#include "unitcreator.hpp"
#include "BattleField.hpp"
#include "battlefielditerator.hpp"
#include "mediator.hpp"

void printBattleField(std::shared_ptr<BattleField> battleField) {
    for (int i = 0; i < battleField->getHeight(); ++i) {
        for (int  j = 0; j < battleField->getWidth(); ++j) {
            FieldCell& cell = battleField->getFieldCell(Position2D(j, i));
            if (cell.isEmpty()) {
                std::cout << "- ";
            }
            else {
                std::cout <<cell.getUnit()->getUnitName()[0]<<" ";
            }
        }
        std::cout << '\n';
    }
}


void test1(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
    std::shared_ptr<Mediator> mediator(new Mediator(battleField));
    
    UnitCreator unitCreator;
    auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
    auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
    auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
    auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
    auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


    battleField->addUnit(archer);
    battleField->addUnit(dragon);
    battleField->addUnit(swordman);
    battleField->addUnit(vampire);
    battleField->addUnit(ballistic);


    battleField->getFieldCell(Position2D(5,4)).getUnit()->moveRight();

    std::cout<< "BattleField created: " <<battleField->getWidth() <<" "<<battleField->getHeight()<<"\n";
    
    battleField->getFieldCellInfo(Position2D(5,4));
    battleField->getFieldCellInfo(Position2D(6,4));
    battleField->getFieldCellInfo(Position2D(6,7));
    printBattleField(battleField);

    std::cout<<"deleting unit from battleField\n";
    battleField->deleteUnit(archer);
//    battleField->deleteUnitCord(Position2D(6,7));
    
    battleField->getFieldCellInfo(Position2D(2,2));
    battleField->getFieldCellInfo(Position2D(6,7));
    printBattleField(battleField);
}
void test2(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
       std::shared_ptr<Mediator> mediator(new Mediator(battleField));
       
       UnitCreator unitCreator;
       auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
       auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
       auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
       auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
       auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


       
       battleField->addUnit(archer);
       battleField->addUnit(dragon);
       battleField->addUnit(swordman);
       battleField->addUnit(vampire);
       battleField->addUnit(ballistic);
    
    printBattleField(battleField);
    auto it = std::unique_ptr<BattleFieldIterator>(new BattleFieldIterator(*battleField));
    for (it->first(); it->hasNext(); ++*it) {
        if (!(**it).isEmpty()) {
            (**it).getUnit()->getUnitInfo();
        }
    }
}
void test3(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
       std::shared_ptr<Mediator> mediator(new Mediator(battleField));
       
       UnitCreator unitCreator;
       auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
       auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
       auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
       auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
       auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


       
       battleField->addUnit(archer);
       battleField->addUnit(dragon);
       battleField->addUnit(swordman);
       battleField->addUnit(vampire);
       battleField->addUnit(ballistic);
    
        std::cout<<"BEFORE MOVEMENT\n";
       printBattleField(battleField);
    
       while (archer->moveRight()) {
               ballistic->moveTop();
               dragon->moveLeft();
       }
    std::cout<<"\nAFTER MOVEMENT\n";
      printBattleField(battleField);

}
void test4(){
    std::shared_ptr<BattleField> battleField(new BattleField(10, 10));
       std::shared_ptr<Mediator> mediator(new Mediator(battleField));
       
       UnitCreator unitCreator;
       auto archer = unitCreator.createArcher(Position2D(2,2), mediator);
       auto dragon = unitCreator.createDragon(Position2D(6,7), mediator);
       auto swordman = unitCreator.createSwordMan(Position2D(5,4), mediator);
       auto vampire = unitCreator.createVampire(Position2D(9,2), mediator);
       auto ballistic = unitCreator.createBallistic(Position2D(4,8), mediator);


       
       battleField->addUnit(archer);
       battleField->addUnit(dragon);
       battleField->addUnit(swordman);
       battleField->addUnit(vampire);
       battleField->addUnit(ballistic);
    
    std::shared_ptr<BattleField> newField = battleField;

    
      printBattleField(newField);
}


int main() {
//    test1();
//    test2();
//    test3();
    test4();
    return 0;
}
