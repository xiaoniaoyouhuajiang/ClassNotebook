#ifndef OOP1_COMMAND_H
#define OOP1_COMMAND_H

#include "Field.h"
#include "Mediator.h"
#include "Adapter.h"

class BaseCommand{
public:
    virtual void execute() = 0;
protected:
    BaseCommand(Field* field): field(field) {}
    Field* field;
};

class SetBaseCommand: public BaseCommand{
private:
    int x, y, maxCount, health;
    Adapter* adapter;
public:
    SetBaseCommand(Field* field, int x, int y, int maxCount, int health, Adapter* adapter) : BaseCommand(field), x(x), y(y), maxCount(maxCount), health(health), adapter(adapter) {
    }
        void execute() override{
            field->createBase(x, y, maxCount, health, adapter);
        }
};

class AttackUnitCommand: public BaseCommand{
private:
    int number;
    Unit* current;
    std::string command;
public:
    AttackUnitCommand(Field* field, int number) : BaseCommand(field), number(number) {
    }

    void execute() override {

        if (number == 1)
            current = field->base1->getUnit();
        else if (number == 2)
            current = field->base2->getUnit();
        else
            current = field->base3->getUnit();

        while(true){
            std::cout << "Unit "<< current->name << " x: " << field->findUnit(current)->x << " y: " << field->findUnit(current)->y <<std::endl;
            std::cin >> command;
            if (command == "n") {
                if (number == 1)
                    current = field->base1->getUnit();
                else if (number == 2)
                    current = field->base2->getUnit();
                else
                    current = field->base3->getUnit();
            }
            else if (command == "w"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 2);
                else
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 1);
                break;
            }
            else if (command == "s"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 2);
                else
                    current->mediator->attack(current, field->findUnit(current)->x, field->findUnit(current)->y - 1);
                break;
            }
            else if (command == "a"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x - 2, field->findUnit(current)->y);
                else
                    current->mediator->attack(current, field->findUnit(current)->x - 1, field->findUnit(current)->y);
                break;
            }
            else if (command == "d"){
                if (current->name == 's' || current->name == 'k')
                    current->mediator->attack(current, field->findUnit(current)->x + 2, field->findUnit(current)->y);
                else
                    current->mediator->attack(current, field->findUnit(current)->x + 1, field->findUnit(current)->y);
                break;
            }
        }


    }
};

class StatusBaseCommand: public BaseCommand{
private:
    int number;
public:
    StatusBaseCommand(Field* field, int number) : BaseCommand(field), number(number) {
    }
    void execute() override{

        if (number == 1){
            std::cout << "Base number 1" <<std::endl;
            std::cout << "x: " << field->base1->BaseX << "  y: " << field->base1->BaseY << std::endl;
            std::cout << "Health: " << field->base1->health << std::endl;
            std::cout << "MaxCountUnit: " << field->base1->maxCountUnit << std::endl;
            std::cout << "Count unit: " << field->base1->countUnit << std::endl;
            std::cout << "Units of base: " << std::endl;
            field->base1->printUnit();
        }
        else if (number == 2){
            std::cout << "Base number 2" <<std::endl;
            std::cout << "x: " << field->base2->BaseX << "  y: " << field->base2->BaseY << std::endl;
            std::cout << "Health: " << field->base2->health << std::endl;
            std::cout << "MaxCountUnit: " << field->base2->maxCountUnit << std::endl;
            std::cout << "Count unit: " << field->base2->countUnit << std::endl;
            std::cout << "Units of base: " << std::endl;
            field->base2->printUnit();
        }
        else{
            std::cout << "Base number 3" <<std::endl;
            std::cout << "x: " << field->base3->BaseX << "  y: " << field->base3->BaseY << std::endl;
            std::cout << "Health: " << field->base3->health << std::endl;
            std::cout << "MaxCountUnit: " << field->base3->maxCountUnit << std::endl;
            std::cout << "Count unit: " << field->base3->countUnit << std::endl;
            std::cout << "Units of base: " << std::endl;
            field->base3->printUnit();
        }

    }
};

class MoveUnitCommand: public BaseCommand{
private:
    int number;
    std::string command;
    Unit* current;
public:
    MoveUnitCommand(Field* field, int number) : BaseCommand(field), number(number) {
    }
    void execute() override{

        if (number == 1)
            current = field->base1->getUnit();
        else if (number == 2)
            current = field->base2->getUnit();
        else
            current = field->base3->getUnit();

            while(true){
                std::cout << "Unit "<< current->name << " x: " << field->findUnit(current)->x << " y: " << field->findUnit(current)->y <<std::endl;
                std::cin >> command;
                if (command == "n") {
                    if (number == 1)
                        current = field->base1->getUnit();
                    else if (number == 2)
                        current = field->base2->getUnit();
                    else
                        current = field->base3->getUnit();
                }
                else if (command == "w"){
                    field->moveUnitUp(current);
                    break;
                }
                else if (command == "s"){
                    field->moveUnitDown(current);
                    break;
                }
                else if (command == "a"){
                    field->moveUnitLeft(current);
                    break;
                }
                else if (command == "d"){
                    field->moveUnitRight(current);
                    break;
                }
            }
        }
};

class CreateUnitCommand: public BaseCommand{
private:
    int number;
    char character;
    Mediator* mediator;
    Adapter* adapter;
public:
    CreateUnitCommand(Field* field, Mediator* mediator, Adapter* adapter, int number) : BaseCommand(field), mediator(mediator), adapter(adapter), number(number) {

    }
    void execute() override{

        if (number == 1) {
            int capacity = field->base1->getCapacityUnit();
            for (int i = 0; i < capacity; i++) {
                std::cout << "Enter name of unit" << std::endl;
                std::cin >> character;
                if (!field->base1->createUnit(character, mediator, adapter)){
                    std::cout << "The area near base is limited" << std::endl;
                    break;
                }
            }
            std::cout << "Units has been set"<<std::endl;
        }

        else if (number == 2){
            int capacity = field->base2->getCapacityUnit();
            for (int i = 0; i < capacity; i++) {
                std::cout << "Enter name of unit" << std::endl;
                std::cin >> character;
                if (!field->base2->createUnit(character, mediator, adapter)){
                    std::cout << "The area near base is limited" << std::endl;
                    break;
                }
            }
            std::cout << "Units has been set"<<std::endl;
        }

        else{
            int capacity = field->base3->getCapacityUnit();
            for (int i = 0; i < capacity; i++) {
                std::cout << "Enter name of unit" << std::endl;
                std::cin >> character;
                if (!field->base3->createUnit(character, mediator, adapter)){
                    std::cout << "The area near base is limited" << std::endl;
                    break;
                }
            }
            std::cout << "Units has been set"<<std::endl;
        }

    }
};


#endif //OOP1_COMMAND_H
