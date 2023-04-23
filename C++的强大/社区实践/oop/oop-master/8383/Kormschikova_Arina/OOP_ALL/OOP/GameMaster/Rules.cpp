#include "Rules.h"
#include "States.h"
#include "GameMaster.h"
#include "GameEntity.h"
void Rules::transitionTo(States* newState){
    if(this->currentState != nullptr){
        delete this->currentState;
    }
    this->currentState = newState;
    if(newState != nullptr){
        this->currentState->setContext(this);
    }
}

bool Rules::request(){
    if(currentState != nullptr){
        currentState->actions();
        return true;
    }
    return false;
}
//------------------------------------------//

void RuleBattleBetweenTeams::gameProcess(){
    mode mode = this->modeR;
    bool requestRes = false;
    transitionTo(new SwitchState(this));
    requestRes = this->request();
    switch (mode) {
        case TWOPLAYERS:
             for(int i = 0; i < gameMaster->countTeam - 1; i++){
                       transitionTo(new BasePlacementState(this));
                       requestRes = this->request();
                       transitionTo(new SwitchState(this));
                       requestRes = this->request();
            }
            while(requestRes == true){
                requestRes = this->request();
            }
            break;
        case ONEPLAYER:
            gameMaster->countTeam = 2;
            gameMaster->enemies = nullptr;
            for(auto it  = gameMaster->teams.begin(); it != gameMaster->teams.end();it++){
                if ((*it)->isActive == false && (*it)->type == PLAYER){
                    gameMaster->teams.erase(it);
                    break;
                }
            }
            transitionTo(new BasePlacementState(this));
            requestRes = this->request();
            transitionTo(new GameCycleState(this));
          
            while(requestRes == true){
                requestRes = this->request();
            }
            return;
        default:
            break;
    }
    
}

void RuleSurvival::gameProcess(){
    bool requestRes = false;
    transitionTo(new SwitchState(this));
    requestRes = this->request();
    gameMaster->countTeam = 2;
    gameMaster->enemies = nullptr;
    for(auto it  = gameMaster->teams.begin(); it != gameMaster->teams.end();it++){
        if ((*it)->isActive == false && (*it)->type == PLAYER){
            gameMaster->teams.erase(it);
            break;
        }
    }
    transitionTo(new SpawnUnitForSurv(this));
     while(requestRes == true){
          requestRes = this->request();
     }
}
