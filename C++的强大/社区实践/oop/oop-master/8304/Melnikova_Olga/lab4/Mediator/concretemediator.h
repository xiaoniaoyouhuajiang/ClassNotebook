//#include "mediator.h"
//#include "component.h"
#pragma once
#include "handlers/handler.h"
#include "handlers/addhandler.h"
#include "handlers/attackhandler.h"
#include "handlers/movehandler.h"
#include "handlers/movetoneutral.h"
#include "target.h"
#include "adapter.h"
#include "adaptee.h"
#include "proxy.h"

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

    void ClientCode(const Target *target, std::string str){
        target->Request(str);
    }

  void Notify(bool logToFile, bool logToTerminal, bool withoutLog) {
      Target *target = new Target;
      Adaptee* adaptee = new Adaptee;
      Proxy* proxy = new Proxy(adaptee, logToFile, logToTerminal, withoutLog);
      Adapter* adapter = new Adapter(proxy);
      std::string numBase;
      if(currNumBase){
          numBase = "1";
      }else{
          numBase = "2";
      }

      h++;
      w++;
      if(!(*isUnitSelected)){
          // что в ячейке, которую мы выделили

          if(game->field->cells(w,h).innerObject == NULL){
              ClientCode(adapter, "Пользователь:    Выделение пустой ячейки");
              return;
          }
          if((game->field->cells(w,h).innerObject->isUnit) && (((Unit*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){
              *isUnitSelected = true;
              *selectedUnit = game->field->cells(w,h).innerObject;
              ClientCode(adapter, "Пользователь:    Выделение своего юнита");
          }else if((game->field->cells(w,h).innerObject->isBase) && (((Base*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){ // (своя)
              // create new Unit
              AddHandler* handler = new AddHandler(game);
  /* + */     handler->Add((Base*)game->field->cells(w,h).innerObject);
              *currNumBase = !(*currNumBase);
              ClientCode(adapter, "Пользователь:    Выделение своей базы");
              ClientCode(adapter, "База" + numBase +":  Создание юнита");
          }
      }else{ //if (isUnitSelected)
          if(game->field->cells(w,h).innerObject == NULL){
              //перемещение
              MoveHandler* handler = new MoveHandler(game);
  /* + */     handler->Move((Unit*)(*selectedUnit), w, h);
              *isUnitSelected = false;
              *currNumBase = !(*currNumBase);
              ClientCode(adapter, "Пользователь:    Выделение пустой ячейки");
              ClientCode(adapter, "База" + numBase +":  Перемещение юнита");

          }
          //если выделен свой другой юнит
          else if((game->field->cells(w,h).innerObject->isUnit) && (((Unit*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){
              *selectedUnit = game->field->cells(w,h).innerObject;
              ClientCode(adapter, "Пользователь:    Выделение своего юнита");
          //если выделена своя база
          }else if((game->field->cells(w,h).innerObject->isBase) && (((Base*)game->field->cells(w,h).innerObject)->numBase == *currNumBase)){
              *isUnitSelected = false;
              // create new Unit
              AddHandler* handler = new AddHandler(game);
  /* + */     handler->Add((Base*)game->field->cells(w,h).innerObject);
              *currNumBase = !(*currNumBase);
              ClientCode(adapter, "Пользователь:    Выделение своей базы");
              ClientCode(adapter, "База" + numBase +":  Создание юнита");

          //если выделен юнит или база врага
          }else if(((game->field->cells(w,h).innerObject->isUnit) && (((Unit*)game->field->cells(w,h).innerObject)->numBase != *currNumBase)) || ((game->field->cells(w,h).innerObject->isBase) && (((Base*)game->field->cells(w,h).innerObject)->numBase != *currNumBase))){
              //атака - selectedUnit по this->game->field->cells(h,w).innerObject
              AttackHandler* handler = new AttackHandler(game);
  /* + */     handler->Attack((Unit*)(*selectedUnit), game->field->cells(w,h).innerObject);
              *isUnitSelected = false;
              *currNumBase = !(*currNumBase);
              ClientCode(adapter, "Пользователь:    Выделение юнита или базы врага");
              ClientCode(adapter, "База" + numBase +":  Атака юнита или базы врага");

          //если выделен нейтральный
          }else if((game->field->cells(w,h).innerObject->isNeutral)){
              //перемещение
              MoveToNeutral* handler = new MoveToNeutral(game);
  /* + */     handler->MoveToNeutr((Unit*)(*selectedUnit), (NeutralObject*)game->field->cells(w,h).innerObject);
              *isUnitSelected = false;
              *currNumBase = !(*currNumBase);
              ClientCode(adapter, "Пользователь:    Выделение нейтрального объекта");
              ClientCode(adapter, "База" + numBase +":  Перемещение юнита");

          }
      }
  }
};
