//
// Created by anton on 6/1/20.
//

#include "Composer.h"

#include "../Mediator.h"

//Composer::Composer(bool sync, const std::weak_ptr<Actor> &actor, const std::shared_ptr<ISender> &sender,const std::shared_ptr<Mediator> &mediator) : sync(sync), actor(actor), sender(sender),mediator(mediator) {}

const std::pair<int, int> &Composer::getSelectionA() const {
    return mediator->getSelectionA();
}

const std::pair<int, int> &Composer::getSelectionB() const {
    return mediator->getSelectionB();
}

void Composer::setSelectionA(const std::pair<int, int> &selectionA) {
    std::unique_ptr<CommandSelect> cmd = std::make_unique<CommandSelect>(actor,true,selectionA.first,selectionA.second);
    if(sync){
        sender->set(std::move(cmd));
    }else{
        sender->setAndSend(std::move(cmd));
    }
}

void Composer::setSelectionB(const std::pair<int, int> &selectionB) {
    std::unique_ptr<CommandSelect> cmd = std::make_unique<CommandSelect>(actor,false,selectionB.first,selectionB.second);
    send(std::move(cmd));
}

bool Composer::act() {
    std::unique_ptr<CommandInteract> cmd = std::make_unique<CommandInteract>(actor, true);
    send(std::move(cmd));
    return false;
}

bool Composer::step() {
    std::unique_ptr<CommandInteract> cmd = std::make_unique<CommandInteract>(actor, false);
    send(std::move(cmd));
    return false;
}

std::vector<std::vector<FlyCell>> Composer::getFW() {
    return mediator->getFW();
}

bool Composer::summon(int x, int y, UnitClass unitClass) {
    std::unique_ptr<CommandSummon> cmd = std::make_unique<CommandSummon>(actor,unitClass,x,y);
    send(std::move(cmd));
    return false;
}

void Composer::setSync(bool sync) {
    Composer::sync = sync;
}

void Composer::send(std::unique_ptr<AbstractCommand> command) {
    if(sync){
        sender->set(std::move(command));
    }else{
        sender->setAndSend(std::move(command));
    }
}

void Composer::exit() {
    std::unique_ptr<CommandExit> cmd = std::make_unique<CommandExit>(actor);
    send(std::move(cmd));
}

void Composer::restart() {
    std::unique_ptr<CommandExit> cmd = std::make_unique<CommandExit>(actor);
    send(std::move(cmd));
}

void Composer::setSender(const std::shared_ptr<ISender> &sender) {
    Composer::sender = sender;
}

Composer::Composer(bool sync, const std::weak_ptr<Actor> &actor, const std::shared_ptr<Mediator> &mediator) : sync(
        sync), actor(actor), mediator(mediator) {}

std::pair<int, std::pair<int, int>> Composer::getBaseStats(Devotion devotion) {
    return mediator->getBaseStats(devotion);
}


