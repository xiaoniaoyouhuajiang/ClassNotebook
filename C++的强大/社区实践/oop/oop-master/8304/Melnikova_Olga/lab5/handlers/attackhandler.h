#ifndef ATTACKHANDLER_H
#define ATTACKHANDLER_H
#include "abstracthandler.h"

class AttackHandler : public AbstractHandler
{
public:
    Game<Rules>* game;
    AttackHandler(Game<Rules>* game){
        this->game = game;
    }
    bool Attack(Unit* who, Object* whom) override {
      if(who->attackRadius >= abs(who->x + who->y - whom->x - whom->y)){
          AttackUnit* command = new AttackUnit(game, who, whom);
          command->Execute();
          game->isActionDone = true;
          if(whom->numBase){
              game->isAttackDone = 2;
          }else{
              game->isAttackDone = 1;
          }
      }else{
          return false;
      }
    }

};

#endif // ATTACKHANDLER_H
