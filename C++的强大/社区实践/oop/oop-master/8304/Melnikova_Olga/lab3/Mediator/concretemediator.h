//#include "mediator.h"
//#include "component.h"
#include "handlers/handler.h"
#include "handlers/addhandler.h"
#include "handlers/attackhandler.h"
#include "handlers/movehandler.h"
#include "handlers/movetoneutral.h"


class ConcreteMediator {
 private:
    Game* game;
    int h;
    int w;
    bool* isUnitSelected;
    Object** selectedUnit;
    int* currNumBase;


 public:
    ConcreteMediator(Game* game, int h, int w, bool* isUnitSelected, Object** selectedUnit, int* currNumBase)
        :game(game), h(h), w(w), isUnitSelected(isUnitSelected), selectedUnit(selectedUnit), currNumBase(currNumBase) {}


  void Notify() {
      h++;
      w++;
      if(!(*isUnitSelected)){
          // что в ячейке, которую мы выделили

          if(game->field->cells(w,h).innerObject == NULL)
              return;
          if((game->field->cells(w,h).innerObject->isUnit) && (((Unit*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){ //сегфолт
              *isUnitSelected = true;
              *selectedUnit = game->field->cells(w,h).innerObject;
          }else if((game->field->cells(w,h).innerObject->isBase) && (((Base*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){ // (своя)
              // create new Unit
              AddHandler* handler = new AddHandler(game);
  /* + */     handler->Add((Base*)game->field->cells(w,h).innerObject);
              *currNumBase = !(*currNumBase);

          }
      }else{ //if (isUnitSelected)
          if(game->field->cells(w,h).innerObject == NULL){
              //перемещение
              MoveHandler* handler = new MoveHandler(game);
  /* + */     handler->Move((Unit*)(*selectedUnit), w, h);
              *isUnitSelected = false;
              *currNumBase = !(*currNumBase);

          }
          //если выделен свой другой юнит
          else if((game->field->cells(w,h).innerObject->isUnit) && (((Unit*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){
              *selectedUnit = game->field->cells(w,h).innerObject;
          //если выделена своя база
          }else if((game->field->cells(w,h).innerObject->isBase) && (((Base*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){
              *isUnitSelected = false;
              // create new Unit
              AddHandler* handler = new AddHandler(game);
  /* + */     handler->Add((Base*)game->field->cells(w,h).innerObject);
              *currNumBase = !(*currNumBase);

          //если выделен юнит или база врага
          }else if(((game->field->cells(w,h).innerObject->isUnit) && (((Unit*)game->field->cells(w,h).innerObject)->numBase != *currNumBase)) || ((game->field->cells(w,h).innerObject->isBase) && (((Base*)game->field->cells(w,h).innerObject)->numBase != *currNumBase))){
              //атака - selectedUnit по this->game->field->cells(h,w).innerObject
              AttackHandler* handler = new AttackHandler(game);
  /* + */     handler->Attack((Unit*)(*selectedUnit), game->field->cells(w,h).innerObject);
              *isUnitSelected = false;
              *currNumBase = !(*currNumBase);

          //если выделен нейтральный
          }else if((game->field->cells(w,h).innerObject->isNeutral)){
              //перемещение
              MoveToNeutral* handler = new MoveToNeutral(game);
  /* + */     handler->MoveToNeutr((Unit*)(*selectedUnit), (NeutralObject*)game->field->cells(w,h).innerObject);
              *isUnitSelected = false;
              *currNumBase = !(*currNumBase);

          }
      }
  }
};
