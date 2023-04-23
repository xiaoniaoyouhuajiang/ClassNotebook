#include "basecommand.h"


map<string, int> BaseCommand::baseInfo()
{
    map<string, int> information;
    information["base number: "] = base->getBaseNumb();
    information["x position base: "] = base->getX();
    information["y position base: "] = base->getY();
    information["unit count in base: "] = base->getUnitCount();
    information["max unit in base: "] = base->getMaxCount();
    information["base health: "] = base->getHealth();
    information["units in base:"  + base->getUnits()->getName()] = base->getUnitCount();
    return information;
}

map<string, int> BaseCommand::unitAdd()
{
    map<string, int> information;
    Data data = params.find("addParams")->second;
    try {
        Unit* u = base->createUnit(data.unitType);
        u->setX(static_cast<unsigned>(base->getX()));
        u->setY(static_cast<unsigned>(base->getY()));
        information["unit added on pos x: "]=base->getX();
        information["unit added on pos y: "]=base->getY();
        information["unit added in base num: "]=base->getBaseNumb();
        information["unit added with name:" + u->getName()]=-1;

    }catch (out_of_range& e) {
        information[e.what()]=0;
    }catch(invalid_argument& e){
        information[e.what()]=0;
    }
    return information;
}

map<string, int> BaseCommand::noSuchAct()
{
    map<string, int> information;
    information["no such action"] = 0;
    return information;
}

BaseCommand::BaseCommand(Base *base, Actions action, map<string, Data> param)
{
    this->base = base;
    this->action = action;
    this->params = param;
}

map<string, int> BaseCommand::mainInfoAboutObj()
{

    if(action == BASE_INFO){
       return baseInfo();
    }else if(action == UNIT_ADD){
       return unitAdd();
    }else{
        return noSuchAct();
    }

}
