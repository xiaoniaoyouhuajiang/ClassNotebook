
#include <stdio.h>
#include "States.h"
#include "Rules.h"
#include "GameMaster.h"
#include "GameEntity.h"
#include <iostream>
void States::setContext(Rules *context){
    this->context = context;
}



void GameCycleState::actions(){
    cycleEnd res;
    res = context->gameMaster->gameCycle();
    switch (res) {
        case NEXT:
            if(context->modeR == SECONDRULE){
                this->context->transitionTo(new NPCState(context));
                 this->context->countCycle++;
                std::cout<<context->maxCycle - context->countCycle<<" cycles left"<<std::endl;;
            }
            else{
                this->context->transitionTo(new CheckingVictoryStates(context));
            }
            break;
        case EXIT:
            this->context->transitionTo(new EndGameState(context));
        default:
            break;
    }
    return;
}

void SwitchState::actions(){
    if(context->gameMaster->units != nullptr){
        context->gameMaster->units->isActive = false;
    }
    do{
    context->gameMaster->units = context->gameMaster->teams.front();
    context->gameMaster->units = context->gameMaster->teams.front();
    context->gameMaster->teams.pop_front();
    context->gameMaster->teams.push_back(context->gameMaster->units);
    }while(context->gameMaster->units->isDefeated == true || context->gameMaster->units->type == NPC);
    
    context->gameMaster->units->isActive = true;
    
    for(auto it = context->gameMaster->teams.begin(); it !=context->gameMaster->teams.end(); it++){
        if((*it)->isActive == false && (*it)->type != NPC){
            context->gameMaster->enemies = (*it);
            break;
        }
    }
    
    this->context->transitionTo(new GameCycleState(context));
    return;
}

void BasePlacementState::actions(){
    context->gameMaster->setBase();
    return;
}

void EndGameState::actions(){
    context->transitionTo(nullptr);
    return;
}

void CheckingVictoryStates::actions(){
    bool result;
    if(context->modeR == ONEPLAYER){
        result = (context->gameMaster->aggressiveNPC->units.size() == 0)? true:false;
    }
    else{
        result = context->gameMaster->checkingVictory();
    }
    if(result == false){
        this->context->transitionTo(new NPCState(context));
    }
    else{
        std::cout<<"The remaining team won this game!"<<std::endl;
        this->context->transitionTo(new EndGameState(context));
    }
    return;
}

void NPCState::actions(){
    std::cout<<"------------NPC MOVE------------"<<std::endl;
    
    if(context->gameMaster->aggressiveNPC->units.size() < 3 && context->modeR == SECONDRULE){
        this->context->transitionTo(new SpawnNPC(context));
        return;
        
    }
    
    context->gameMaster->moveNPC();
    
    if(context->modeR == TWOPLAYERS){
        this->context->transitionTo(new SwitchState(context));
    }
    else if(context->modeR == ONEPLAYER){
        this->context->transitionTo(new GameCycleState(context));
    }else{
        this->context->transitionTo(new CheckingVictoryForSurvStates(context));
    }
    std::cout<<"------------NPC MOVE END------------"<<std::endl;
}

void SpawnUnitForSurv::actions(){
    context->gameMaster->spawnUForSurv();
    this->context->transitionTo(new GameCycleState(context));
}


void SpawnNPC::actions(){
    context->gameMaster->spawnNPCForSurv();
    this->context->transitionTo(new NPCState(context));
}

void CheckingVictoryForSurvStates::actions(){
    if (context->gameMaster->aggressiveNPC->units.size() == 0 || context->maxCycle == context->countCycle){
        std::cout<<"You won this game!"<<std::endl;
        this->context->transitionTo(new EndGameState(context));
        return;
    }
    if(context->gameMaster->units->units.size() == 0){
        std::cout<<"You lose this game!"<<std::endl;
        this->context->transitionTo(new EndGameState(context));
        return;
    }
    this->context->transitionTo(new GameCycleState(context));
}
