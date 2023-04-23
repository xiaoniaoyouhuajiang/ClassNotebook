//
//  Game.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Game.hpp"



void Game::startGame() {
    
    std::string s;
    std::ofstream f;
    ProxyLog *log;
    
    std::cout << "Запись логов в файл \'f\' или в консоль \'c\'. Без записи  \'n\'" << std::endl;
    std::cin >> s;
    
    if (s.length() == 1 && s[0] == 'f'){
        std::cout << "File" << std::endl;
        log = new ProxyLog (true, true);
        
    } else if (s.length() == 1 && s[0] == 'c'){
        std::cout << "Console" << std::endl;
        log = new ProxyLog (true, false);
            
    } else if (s.length() == 1 && s[0] == 'n'){
        std::cout << "No" << std::endl;
        log = new ProxyLog (false, false);
                
    } else {
        std::cout << "Error input" << std::endl;
        return;
    }
    
  
    actionHandler = new CommandHandler (log);
    
    std::cout << "Загрузить сохранение y/n" << std::endl;
    std::cin >> s;
    
    if (s.length() == 1 && s == "y"){
        
        firstSave = new BaseSnapshot;
        secondSave = new BaseSnapshot;
        fieldSave = new FieldSnapshot;
        
        SaveFile b(false);
        
        if (b.reed(firstSave, secondSave, fieldSave) == false){
            return;
        }
        
        field = new Field();
        first = new Base(this);
        second = new Base(this);
        
        field->restore(fieldSave);
        first->restore(firstSave, log, field);
        second->restore(secondSave, log, field);
        
        
    } else if (s.length() == 1 && s == "n"){

        height = size;
        width = size;
        
        field = new Field();
        
        if (!(field->createField(height, width))) return;
        
        
        
        first = new Base (1, width-1, 0, field, log, isProt, this);
        second = new Base (2, 0, height-1, field, log, isProt, this);
        
        
        
        first->setFirstUnits(field);                        /// расстановка юнитов на позиции
        second->setFirstUnits(field);
        
        first->setNeutralObjects(field);                    /// расстановка нейтральных объктов на позиции
        second->setNeutralObjects(field);
        
    } else {return;}
    
    
    
    std::cout << "Start" << std::endl;
    
    Facade* motion = new Facade(field, first, second);

    bool endGame = true;
    bool saveGame = false;
    bool loadGame = false;
    bool newGame = false;
    
    motion->printField();                           /// печать поля
    
    motion->printPoints();                          /// печать характеристик юнитов
    
    
    
    int n = rand()%2;
               
    if (n == 0) {
        state.nextState();
    }
               
    std::cout << "Ходит игрок " << state.getState() +1 << std::endl;
    
    
    do{
        
      
        
        if (specialFirst > 0) specialFirst--;
        if (specialSecond > 0) specialSecond--;
        
        
        try{
        
        
        
        if (action(endGame, saveGame, loadGame)){
            motion->printField();
            motion->printPoints();
            //printf("\033c");
            
            
            if (winner != 0) {
                
                std::cout <<  "Игрок " << winner << " победил" << std::endl;
                return;
            }
            
//
//            if (saveGame == false && loadGame == false && newGame == false){
//                n = rand()%2;
//                if (n == 0) {state.nextState();}
//                std::cout << "Ходит игрок " << state.getState() +1 << std::endl;
//            }
//            
            
            
        } else {
            std::cout << "Error motion" << std::endl;
        }
            
            
        }
        
        
        
        
        
        
        
        catch (OutOfField &ex) {
            
            ex.writeErr();
        }
        catch (UnknownUnit &ex) {
            ex.writeErr();
        }
        catch (ErrorSpec &ex) {
            ex.writeErr();
        }
        catch (WrongMotion &ex) {
            ex.writeErr();
        }
        catch (WrongGamer &ex) {
            ex.writeErr();
        }
        catch (ErrorSpawn &ex) {
            ex.writeErr();
        }
        
        
        
        
        
        
        
        
        if (saveGame) {
           
            
            std::cout << "Save" << std::endl;
            
            if (firstSave) delete firstSave;
            if (secondSave) delete secondSave;
            if (fieldSave) delete fieldSave;
            
            firstSave = first->saveBase();
            secondSave = second->saveBase();
            fieldSave = field->saveField();
            
            SaveFile a(true);
            a.write(firstSave, secondSave, fieldSave);
            saveGame = false;
        
        } else if (loadGame && firstSave) {
           
            
            
            std::cout << "Load" << std::endl;
            
            delete first;
            delete second;
            delete field;
            
            field = new Field();
            first = new Base(this);
            second = new Base(this);
            
            field->restore(fieldSave);
            first->restore(firstSave, log, field);
            second->restore(secondSave, log, field);
            
            delete motion;
            motion = new Facade(field, first, second);
            motion->printField();
            motion->printPoints();
            loadGame = false;
            
        }
                    
                  
    }while(endGame);
    
    
    
}


bool Game::action(bool &endGame, bool &saveGame, bool &loadGame) {
    
    std::string command;
    char name[3] = {'\0'};
    
    std::cin >> command;
    
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    SpawnHandler *spaw = new SpawnHandler();
    ExitHandler *exit = new ExitHandler();
    MotionHandler *moti = new MotionHandler();
    SpecHandler *spec = new SpecHandler();
    SaveHandler *save = new SaveHandler();
    LoadHandler *load = new LoadHandler();
    
    exit->SetNext(spaw)->SetNext(spec)->SetNext(moti)->SetNext(save)->SetNext(load);
    
    if (!(exit->Handle(command))){
        
        throw WrongMotion (command);
        return false;
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    if (command.find("exit") == 0 && command.length() == 4){
        endGame = false;
        return true;
    }
    
    if (command.find("save") == 0 && command.length() == 4){
        saveGame = true;
        return true;
    }
    
   if (command.find("load") == 0 && command.length() == 4){
       loadGame = true;
       return true;
    }
    
    if (command.find("spec") == 0 && command.length() == 4){
        
        if (std::cin.get() != ' '){
              std::cin.ignore(32767,'\n');
              return false;
          }

        
        std::string unit1;
        std::string unit2;

        std::cin >> unit1;
        
        if (unit1.length() != 2 ) return false;
        
        if (!state.checkState(unit1)){
            
            throw WrongGamer (unit1);
            
            std::cout << "Сейчас ходит другой игрок" << std::endl;
            return false;
        }
        
        std::cin >> unit2;
        if (unit2.length() != 2 ) return false;

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
            
            throw UnknownUnit (unit1);
            
            std::cout << "Юнит не найден"<< std::endl;
            return false;
        } else if (smoker->uid->getUnitID() != 0){
            
            throw ErrorSpec (unit1);
            
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
            
            throw UnknownUnit (unit2);
            
            std::cout << "Юнит не найден"<< std::endl;
            return false;
        }
        
        if (*num == 0){
            mediator.specialAbility(smoker, unit);
            *num += 3;
        } else {
            
            throw ErrorSpec (*num);
            
            
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
        
         if (!state.checkState(gamer)){
             
             throw WrongGamer (gamer);
            std::cout << "Сейчас ходит другой игрок" << std::endl;
             return false;
        }

        
        if (gamer == '1') {
            if (first->spawn(typeUnit, false) == false){
                throw ErrorSpawn (gamer, typeUnit);
            }
        } else  if (gamer == '2') {
            if (second->spawn(typeUnit, false) == false){
                    throw ErrorSpawn (gamer, typeUnit);
            }
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
            
            throw UnknownUnit(name);
            
            std::cout << "Юнит не найден"<< std::endl;
            return false;
        }
        
        if (!state.checkState(name)){
            
            throw WrongGamer(name);
            
            std::cout << "Сейчас ходит другой игрок" << std::endl;
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
            return actionHandler->move(chosenUnit, field, toX, toY);
        } else if (command[1] == 'h') {
            return actionHandler->hit(chosenUnit, field, toX, toY);
        } else {
            return false;
        }
    }
 
    return true;
}

Game::~Game(){
    
    if (field) delete field;
    if (first) delete first;
    if (second) delete second;
    if (actionHandler) delete actionHandler;
}
   

void Game::Update(Unit *unit){
    
    if (unit->getName() == "$1" && winner == 0){
        winner = 2;
    } else {
        winner = 1;
    }
}


Game::Game(bool fastGame, int size){
    
    isProt = fastGame;
    this->size = size;
    
}
