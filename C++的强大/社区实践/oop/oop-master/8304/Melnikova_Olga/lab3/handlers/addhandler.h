#ifndef ADDHANDLER_H
#define ADDHANDLER_H
#include "abstracthandler.h"

class AddHandler : public AbstractHandler
{
public:
    Game* game;
    AddHandler(Game* game);
    Base* Add(Base* object) override {
        bool Archer = false;
        bool CrossBowMan = false;
        bool Knight = false;
        bool SpearMan = false;
        bool HeavyRider = false;
        bool LightRider = false;
        for (Unit* n : object->units){ // не все созданны
            if(n->isArcher){
                Archer = true;
            }else if(n->isCrossBowMan){
                CrossBowMan = true;
            }else if(n->isKnight){
                Knight = true;
            }else if(n->isSpearMan){
                SpearMan = true;
            }else if(n->isHeavyRider){
                HeavyRider = true;
            }else if(n->isLightRider){
                LightRider = true;
            }
        }
        int x = 0;
        int y = 0;
        if(!(object->numBase)){
            for (int i = 1; i<=game->field->H; i++){ //не все клетки заняты, поиск ближайшей свободной
                for (int j = 1; j<=game->field->W; j++){
                    if(game->field->cells(i,j).innerObject == NULL){
                        x=i;
                        y=j;
                        i = game->field->H+1;
                        j = game->field->W+1;
                    }
                }
            }
        }else{
            for (int i = game->field->H; i>1; i--){ //не все клетки заняты, поиск ближайшей свободной
                for (int j = game->field->W; j>1; j--){
                    if(game->field->cells(i,j).innerObject == NULL){
                        x=i;
                        y=j;
                        i = 0;
                        j = 0;
                    }
                }
            }
        }
        if((!Archer && !CrossBowMan && !Knight && !SpearMan && !HeavyRider && !LightRider) || (!x)){
            return nullptr;
        } else {
            //создание
            AddUnit* command;
            if(!Archer){
                command = new AddUnit(game, "Archer", object->numBase, x, y);
            }else if(!CrossBowMan){
                command = new AddUnit(game, "CrossBowMan", object->numBase, x, y);
            }else if(!Knight){
                command = new AddUnit(game, "Knight", object->numBase, x, y);
            }else if(!SpearMan){
                command = new AddUnit(game, "Spearman", object->numBase, x, y);
            }else if(!HeavyRider){
                command = new AddUnit(game, "HeavyRider", object->numBase, x, y);
            }else if(!LightRider){
                command = new AddUnit(game, "LightRider", object->numBase, x, y);
            }else{
                return nullptr;
            }
            command->Execute();
            return AbstractHandler::Add(object);
        }
   }
};

#endif // ADDHANDLER_H
