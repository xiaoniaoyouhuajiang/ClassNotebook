#ifndef ABSTRACTHANDLER_H
#define ABSTRACTHANDLER_H
#include "handler.h"

class AbstractHandler : public Handler
{
private:
     Handler *next_handler_;

public:
     AbstractHandler() : next_handler_(nullptr) {
     }
     Handler *SetNext(Handler *handler) override {
       this->next_handler_ = handler;
       return handler;
     }
     Base* Add(Base* object) override {
       if (this->next_handler_) {
         return this->next_handler_->Add(object);
       }
       return {};
     }
     bool Attack(Unit* who, Object* whom) override {
       if (this->next_handler_) {
         return this->next_handler_->Attack(who, whom);
       }
       return {};
     }
     bool Move(Unit* who, int x2, int y2) override {
       if (this->next_handler_) {
         return this->next_handler_->Move(who, x2, y2);
       }
       return {};
     }
     bool MoveToNeutr(Unit* unit, NeutralObject* obj)  override {
         if (this->next_handler_) {
           return this->next_handler_->MoveToNeutr(unit, obj);
         }
         return {};
    }
};

#endif // ABSTRACTHANDLER_H
