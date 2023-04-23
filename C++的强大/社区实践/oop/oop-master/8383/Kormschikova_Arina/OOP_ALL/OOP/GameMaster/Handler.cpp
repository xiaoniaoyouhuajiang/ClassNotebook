#include <iostream>
#include <sstream>

#include "Command.h"
#include "Units.h"
#include "GameEntity.h"
#include "Map.h"
#include "GameBlock.h"
#include "Base.h"
#include "Handler.h"
#include "GameMaster.h"
#include "Logger.h"
#include "GameVisualization.h"
#include "Exeptions.h"
void update(GameMap &map);

Handler* AbstractHandler::setNext(Handler* handler){
    this->nextHandler = handler;
    return handler;
}


Command* AbstractHandler::handle(char request, Base *base, bool* death, GameMaster* GM){
    if(this->nextHandler){
        return this->nextHandler->handle(request, base, death, GM);
    }
    return {};
}


Command* AttackHandler::handle(char request, Base *base, bool* death, GameMaster* GM){
    if(request == 'f'){
        std::vector<TeamEntity*> enemies;
        if(GM->enemies != nullptr){
            enemies.push_back(GM->enemies);
        }
        enemies.push_back(GM->aggressiveNPC);
        return new AttackCommand(GM->map, enemies, GM->units, GM->units->currentUnit, &(GM->energyForStep));
    }
    return AbstractHandler::handle(request, base, death, GM);
}


Command* MoveHandler::handle(char request, Base *base, bool* death, GameMaster* GM){
    switch (request) {
        case 'w':
            return new MoveCommand(0, -1, GM->units->currentUnit, GM->map, GM->units, death, &(GM->energyForStep));
        case 's':
            return new MoveCommand(0, 1, GM->units->currentUnit, GM->map, GM->units, death, &(GM->energyForStep));
        case 'd':
            return new MoveCommand(1, 0, GM->units->currentUnit, GM->map, GM->units, death, &(GM->energyForStep));
        case 'a':
            return new MoveCommand(-1, 0, GM->units->currentUnit, GM->map, GM->units, death, &(GM->energyForStep));
        default:
            return AbstractHandler::handle(request,base, death, GM);
    }
}


Command* ChangeUnitHandler::handle(char request, Base *base, bool* death, GameMaster* GM){
    if(request == 'u'){
        return new SwitchUnitCommand(GM->units, &(GM->units->currentUnit));
    }
    return AbstractHandler::handle(request, base,  death, GM);
}


Command* BaseControlHandler::handle(char request, Base *base,  bool* death, GameMaster* GM){
    if(request == 'b'){
        Command* command;
        if(base == nullptr){
            std::cout<<"You have no base!"<<std::endl;
            return nullptr;
        }
    
        GM->gameVisualization->update();
        command =  new BaseStatCommand(base);
        command->execute();
        
        base->baseUpdate();
        LogProxy*  loggerP = base->loggerP;
        std::stringstream messageForLog;
        Adapter adapter;
        char input;
        do{
        
            std::cout<<"Enter command for base 'c' - Create unit, 's' - select unit in base, 't' - show stat, 'u' - select unit out of base, 'o' - options"<<std::endl;
            try{
                std::cin>>input;
                messageForLog <<"User input: "<<input<<std::endl;
                loggerP->request(new LogInfo(messageForLog.str()));
                messageForLog.str("");
            }catch(const std::istream::failure& ex){
                messageForLog <<"User input fail "<<input<<std::endl;
                adapter.InfoStr(messageForLog.str());
                adapter.InfoErrorCode(ex.code());
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            
            std::cout<<std::endl;
            switch (input) {
                case 'c':
                    command =  new CreateUnitInBaseCommand(base, &(GM->energyForStep));
                    command->execute();
                    break;
                case 's':
                    command = new SelectUnitInBaseCommand(GM->units, base, GM->map);
                    command->execute();
                    if(GM->units->currentUnit == -1){
                        continue;
                    }
                    return nullptr;
                case 't':
                    command =  new BaseStatCommand(base);
                    command->execute();
                    break;
                case 'u':
                    if(GM->units->size != 0){//base->unitsInBase > base->units.size()
                        command = new SwitchUnitCommand(GM->units, &(GM->units->currentUnit));
                        command->execute();
                        return nullptr;
                    }
                    else{
                        std::cout<<"There are no units out of base!!"<<std::endl;
                        continue;
                    }
                case 'o':
                    command =  AbstractHandler::handle('o',base, death, GM);
                    command->execute();
                    continue;
                default:
                    break;
            }
            
        }while(1);
    }
    
    return AbstractHandler::handle(request,base, death, GM);
}




Command* HelpHandler::handle(char request,  Base *base,  bool* death, GameMaster* GM){
    if(request == 'h'){
        return new HelpCommand;
    }
    return AbstractHandler::handle(request,  base, death, GM);
}

Command* OptionsHandler::handle(char request,  Base *base,  bool *death, GameMaster* GM){
    if(request == 'o'){
        char input;
                Adapter adapter;
        std::stringstream messageForLog;
        do{
            std::cout<<"Enter command s - save, l - load"<<std::endl;
            try{
                std::cin>>input;
                messageForLog <<"User input: "<<input<<std::endl;
                adapter.InfoStr(messageForLog.str());
                messageForLog.str("");
            }
            catch(const std::istream::failure& ex){
               messageForLog <<"User input fail: "<<input<<std::endl;
               adapter.InfoStr(messageForLog.str());
               adapter.InfoErrorCode(ex.code());
               std::cin.clear();
               std::cin.ignore(10000, '\n');
               input = 's';
            }
            switch (input) {
                case 's':
                    return new SaveFCommand(GM->makeMemento());
                case 'l':
                    try{
                        return new LoadFCommand(GM->makeMemento(), GM);
                    }
                    catch(std::ifstream::failure& ex){
                        std::cout<<"FAIL LOAD: ERROR OPEN FILE!"<<std::endl;
                        return nullptr;
                    }
                    
                default:
                    break;
            }
        }while(1);
      //  return new SaveFCommand(GM->makeMemento(),  GM->loggerP);
    }
    
    return AbstractHandler::handle(request, base, death, GM);
}

