#ifndef abstracthandler_hpp
#define abstracthandler_hpp

#include "handler.hpp"

class AbstractHandler : public Handler
{
private:
     std::shared_ptr<Handler> next_handler_;

public:
      AbstractHandler();
     std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler) override {
       this->next_handler_ = handler;
       return handler;
     }
     std::shared_ptr<Unit> CreateUnit(std::shared_ptr<Base> homeBase,std::shared_ptr<Base> enemyBase,std::string type) override {
       if (this->next_handler_) {
         return this->next_handler_->CreateUnit(homeBase, enemyBase,type);
       }
       return {};
     }
    bool Attack(std::shared_ptr<BattleField> battleField,std::shared_ptr<Unit> unit, std::shared_ptr<Adapter> log) override {
       if (this->next_handler_) {
         return this->next_handler_->Attack(battleField,unit,log);
       }
       return {};
     }
     bool MoveUnit(std::shared_ptr<Base> enemyBase,std::shared_ptr<Unit> unit) override {
       if (this->next_handler_) {
         return this->next_handler_->MoveUnit(enemyBase, unit);
       }
       return {};
     }
};

#endif /* abstracthandler_hpp */
