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
    information["field height"] = static_cast<int>(game->getField()->getHeight());
    information["field width"] = static_cast<int>(game->getField()->getWidth());
    information["field max items"] = static_cast<int>(game->getField()->getMaxItems());
    information["count items on field"] = static_cast<int>(game->getField()->getCountOfItems());
    information["count of bases"] = static_cast<int>(game->getBases().size());
    return information;
}

map<string, int> GameCommand::attack()
{
    map<string, int> information;
    FieldCommand com(game->getField(), action, params);
    Unit* u = com.findItem();
    if(!u){
        information["no such unit"] = 0;
        return information;
    }
    try {

        for (Unit* i : game->getUnits())
        {
            if (i == u)
            {
                i->attack(params.find("attack pos")->second.x, params.find("attack pos")->second.y);
                information["attack was"] = 0;
                return information;
            }
        }
    }
    catch (invalid_argument& e) {
        information[e.what()]=0;
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
            information["base was created"] = baseNumb;
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
        game->createNeutral(params.find("addParams")->second.neutralType, x, y);
        information["neutral add"] = NEUTRAL_ADD;
        information["pos x "] = static_cast<int>(x);
        information["pos y "] = static_cast<int>(y);
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
        info[e.what()]=0;
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
