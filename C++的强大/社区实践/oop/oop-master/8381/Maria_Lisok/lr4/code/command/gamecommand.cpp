#include "gamecommand.h"



map<string, int> GameCommand::baseInfo()
{
    map<string, int> information;
    int baseNum = params.find("base num")->second.x;
    if(baseNum >= 0){
        if(static_cast<unsigned>(baseNum) < game->getBases().size()){
            BaseCommand com(game->getBaseByNum(baseNum),action, params);
            return com.mainInfoAboutObj();
        }else{
            information["not base with such number"] = baseNum;
        }
    }else{
        information["base number must be >="] = 0;
    }
    return information;
}

map<string, int> GameCommand::gameInfo()
{
    map<string, int> information;
    information["field height: "] = static_cast<int>(game->getField()->getHeight());
    information["field width: "] = static_cast<int>(game->getField()->getWidth());
    information["field max items: "] = static_cast<int>(game->getField()->getMaxItems());
    information["count items on field: "] = static_cast<int>(game->getField()->getCountOfItems());
    information["count of bases: "] = static_cast<int>(game->getBases().size());
    return information;
}

map<string, int> GameCommand::attack()
{
    map<string, int> information;
    FieldCommand com(game->getField(), action, params);
    Unit* u = com.findItem();
    if(!u){
        information["no such unit"] = -1;
        return information;
    }
    try {

        for (Unit* i : game->getUnits())
        {
            if (i == u)
            {
                int x = params.find("attack pos")->second.x;
                int y = params.find("attack pos")->second.y;
                i->attack(x, y);
                information["attack was"] = -1;
                information["attacker name: "+i->getName()] = -1;
                information["pos x for attack: "]=x;
                information["pos x for attack: "]=y;
                return information;
            }
        }
    }
    catch (invalid_argument& e) {
        information[e.what()]=-1;
        return information;
    }
    information["not such attacker"] = -1;
    return information;
}

map<string, int> GameCommand::move()
{
    FieldCommand com(game->getField(), action, params);
    return com.mainInfoAboutObj();
}

map<string, int> GameCommand::addBase()
{
    map<string, int> information;
    int maxUnitsCount = params.find("addParams")->second.x;
    int health = params.find("addParams")->second.y;
    int x = params.find("pos")->second.x;
    int y = params.find("pos")->second.y;
    int baseNumb = params.find("addParams")->second.base;
    try {
        if(game->getField()->getCell(static_cast<unsigned>(x),static_cast<unsigned>(y))->getBase()){
            throw invalid_argument("there is base on such cell "+to_string(x)+","+to_string(y));
        }
        else{
            game->createBase(maxUnitsCount, health, x, y, baseNumb);
            information["base was created\n base num:"] = baseNumb;
            information["base added on pos x:"] = x;
            information["base added on pos y:"] = y;
        }
    } catch (out_of_range& e) {
        information[e.what()]=0;
    }
    return information;
}

map<string, int> GameCommand::addNeutral()
{
    map<string, int> information;
    unsigned x = static_cast<unsigned>(params.find("addParams")->second.x);
    unsigned y = static_cast<unsigned>(params.find("addParams")->second.y);
    try{
        NeutralType typeNet = params.find("addParams")->second.neutralType;
        game->createNeutral(typeNet, x, y);
        information["pos x "] = static_cast<int>(x);
        information["pos y "] = static_cast<int>(y);
        information["neutral type: "]= typeNet;
    }catch(out_of_range& e){
        information[e.what()]=0;
    }catch(invalid_argument& e){
        information[e.what()]=0;
    }
    return information;
}

map<string, int> GameCommand::addUnit()
{
    int baseNum = params.find("addParams")->second.base;
    Base* base{};
    try {
        base = game->getBaseByNum(baseNum);
    } catch (invalid_argument& e) {
        map<string, int> info;
        info[e.what()]=-1;
        return info;
    }
    CreateMediator* createMed = new CreateMediator(game->getField(), base);
    base->setCreateMediator(createMed);
    game->getField()->setCreateMediator(createMed);
    BaseCommand com(base,action, params);
    return com.mainInfoAboutObj();


}

map<string, int> GameCommand::noSuchAct()
{
    map<string, int> information;
    information["no such action"] = 0;
    return information;
}

GameCommand::GameCommand(Game *game, Actions act, map<string, Data> param)
{
    this->game = game;
    action = act;
    params = param;
}

map<string, int> GameCommand::mainInfoAboutObj()
{
    if(action == GAME_INFO){
        return gameInfo();
    }else if(action == BASE_INFO){
        return baseInfo();
    }else if(action == LAND_INFO || action == NEUTRALS_INFO || action == UNITS_INFO){
        FieldCommand com(game->getField(), action, params);
        return com.mainInfoAboutObj();
    }else if(action == LAND_CELL || action == NEUTRAL_INFO || action == UNIT_INFO){
        FieldCommand com(game->getField(), action, params);
        return com.mainInfoAboutObj();
    }else if(action == MOVE){
        return move();
    }else if(action == ATTACK){
        return attack();
    }else if(action == BASE_ADD){
        return addBase();
    }else if(action == UNIT_ADD){
        return addUnit();
    }else if(action == NEUTRAL_ADD){
        return addNeutral();
    }else{
        return noSuchAct();
    }
}
