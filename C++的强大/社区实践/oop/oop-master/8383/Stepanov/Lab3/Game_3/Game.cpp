//
//  Game.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Game.hpp"



void Game::startGame() {
    
    std::cout << "Start" << std::endl;
    
    height = SIZE;
    width = SIZE;
    
    field = new Field();
    
    if (!(field->createField(height, width))) return;
    
    first = new Base (1, width-1, 0, field);
    second = new Base (2, 0, height-1, field);
    
    Facade motion(field, first, second);
    
    first->setFirstUnits(field);                        /// расстановка юнитов на позиции
    second->setFirstUnits(field);
    
    first->setNeutralObjects(field);                    /// расстановка нейтральных объктов на позиции
    second->setNeutralObjects(field);
    
    

    bool endGame = true;
    
    motion.printField();                           /// печать поля
    
    motion.printPoints();                          /// печать характеристик юнитов
    
    do{
        
        if (specialFirst > 0) specialFirst--;
        if (specialSecond > 0) specialSecond--;
        
        if (action(endGame)){
            motion.printField();
            motion.printPoints();
            //printf("\033c");
            
        }
                    
                  
    }while(endGame);
}


bool Game::action(bool &endGame) {
    
    std::string command;
    char name[3] = {'\0'};
    
    std::cin >> command;
    
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    SpawnHandler *spaw = new SpawnHandler();
    ExitHandler *exit = new ExitHandler();
    MotionHandler *moti = new MotionHandler();
    SpecHandler *spec = new SpecHandler();
    
    exit->SetNext(spaw)->SetNext(spec)->SetNext(moti);
    
    if (!(exit->Handle(command))){
        std::cout << "Error motion" << std::endl;
        std::cin.ignore(32767,'\n');
        return false;
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    if (command.find("exit") == 0 && command.length() == 4){
        endGame = false;
        return true;
    }
    
    if (command.find("spec") == 0 && command.length() == 4){
        
        if (std::cin.get() != ' '){
              std::cin.ignore(32767,'\n');
              return false;
          }
        
        char unit1[3] = {'\0'};
        char unit2[3] = {'\0'};
        
        
        
        unit1[0] = std::cin.get();
        unit1[1] = std::cin.get();
        
        if (std::cin.get() != ' '){
            std::cin.ignore(32767,'\n');
            return false;
        }
        
        unit2[0] = std::cin.get();
        unit2[1] = std::cin.get();
        
        if (std::cin.get() != '\n'){
            std::cin.ignore(32767,'\n');
            return false;
        }
        
        Base *base;
        int *num;
            
        if ('1' <= unit1[0] && unit1[0] <='9') {
            base = second;
            num = &specialSecond;
        } else {
            base = first;
            num = &specialFirst;
        }
            
        Unit* smoker  = base->findUnit(unit1);
            
        if (smoker == nullptr){
            std::cout << "Юнит не найден"<< std::endl;
            return false;
        } else if (smoker->uid->getUnitID() != 0){
            std::cout << "First unit is not Smoker"<< std::endl;
            return false;
        }
        
        if ('1' <= unit2[0] && unit2[0] <='9') {
            base = second;
        } else {
            base = first;
        }
            
        Unit* unit  = base->findUnit(unit2);
            
        if (unit == nullptr){
            std::cout << "Юнит не найден"<< std::endl;
            return false;
        }
        
        if (*num == 0){
            mediator.specialAbility(smoker, unit);
            *num += 3;
        } else {
            std::cout << "You can use spec after " << *num << " moves"<< std::endl;
        }
        return true;
    }
    
    if (command.find("spawn") == 0 && command.length() == 5) {
        
        if (std::cin.get() != ' '){
            std::cin.ignore(32767,'\n');
            return false;
        }
        
        char typeUnit = std::cin.get();
        
        if (std::cin.get() != ' '){
            std::cin.ignore(32767,'\n');
            return false;
        }
        
        char gamer = std::cin.get();
        
        if (std::cin.get() != '\n'){
            std::cin.ignore(32767,'\n');
            return false;
        }
        
        
        if (gamer == '1') {
            return first->spawn(typeUnit, false);
        } else  if (gamer == '2') {
            return second->spawn(typeUnit, false);
        } else {
            return  false;
        }
        return true;
    }
    
    if (command.length() == 2 && (command[0] == 'w' || command[0] == 'a' || command[0] == 's' || command[0] == 'd')){
        
        if (std::cin.get() != ' ') {
            std::cin.ignore(32767,'\n');
            return false;
        }
            
        name[0] = std::cin.get();
        name[1] = std::cin.get();
            
        if (std::cin.get() != '\n'){
            std::cin.ignore(32767,'\n');
            return false;
        }
            
        Base *base;
            
        if ('1' <= name[0] && name[0] <='9') {
            base = second;
        } else {
            base = first;
        }
            
        Unit* chosenUnit  = base->findUnit(name);
            
        if (chosenUnit == nullptr){
            std::cout << "Юнит не найден"<< std::endl;
            return false;
        }
            
        int toX = chosenUnit->getX();
        int toY = chosenUnit->getY();
                       
        switch (command[0]) {
        case 'w':
            toY--;
            break;
                
        case 'a':
            toX--;
            break;
                    
        case 's':
            toY++;
            break;
                    
        case 'd':
            toX++;
            break;
                
        default:
            return false;
            break;
        }
            
            
        if (command[1] == 'm') {
            actionHandler.move(chosenUnit, field, toX, toY);
            return true;
        } else if (command[1] == 'h') {
            actionHandler.hit(chosenUnit, field, toX, toY);
            return true;
        } else {
            return false;
        }
    }
 
    return true;
}



       

