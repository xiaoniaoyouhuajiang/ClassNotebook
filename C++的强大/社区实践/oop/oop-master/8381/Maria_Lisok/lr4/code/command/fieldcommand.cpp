#include "fieldcommand.h"

map<string, int> FieldCommand::landscapeInfo()
{
    map<string, int> information;
    information["heigth"] = static_cast<int>(field->getHeight());
    information["heigth"] = static_cast<int>(field->getHeight());
    for(unsigned i = 0; i < field->getWidth(); i++ ){
        for(unsigned j = 0; j < field->getHeight(); j++ ){
            information["landscape type on pos"+to_string(i)+","+to_string(j)] =
                    field->getCell(i, j)->getLandscape()->getLandscapeTypeEnum();
        }
    }
    return information;
}

map<string, int> FieldCommand::unitsInfo()
{
    map<string, int> information;
    for(unsigned i = 0; i < field->getWidth(); i++){
        for(unsigned j = 0; j < field->getHeight(); j++){
            Unit* u = field->getCell(i, j)->getUnit();
            if(u){
                information["pos x"] = static_cast<int>(i);
                information["pos y"] = static_cast<int>(j);
                information["unit type:"] = u->getTypeEnum();
            }
        }
    }
    if(information.empty()){
        information["no units el"] = 0;
    }
    return information;
}

map<string, int> FieldCommand::neutralslInfo()
{
    map<string, int> information;
    for(unsigned i = 0; i < field->getWidth(); i++){
        for(unsigned j = 0; j < field->getHeight(); j++){
            NeutralObj* n = field->getCell(i, j)->getNeutral();
            if(n){
                information["pos x"] = static_cast<int>(i);
                information["pos y"] = static_cast<int>(j);
                information["neutal type:"] = n->getTypeEnum();
            }
        }
    }
    if(information.empty()){
        information["no neutrals el"] = 0;
    }
    return information;
}

map<string, int> FieldCommand::neutrallInfo()
{
    map<string, int> information;
    unsigned x = static_cast<unsigned>(params.find("infoParams")->second.x);
    unsigned y = static_cast<unsigned>(params.find("infoParams")->second.y);
    NeutralObj* neutr = field->getCell(x, y)->getNeutral();
    if(neutr){
        information["neutal pos x"] = static_cast<int>(x);
        information["neutal pos y"] = static_cast<int>(y);
        information["neutal type:"] = neutr->getTypeEnum();
    }
    else{
        information["no neutral el on such cell"] = 0;
    }
    return information;
}

map<string, int> FieldCommand::unitlInfo()
{
    map<string, int> information;
    unsigned x = static_cast<unsigned>(params.find("infoParams")->second.x);
    unsigned y = static_cast<unsigned>(params.find("infoParams")->second.y);
    Unit* un = field->getCell(x, y)->getUnit();
    if(un){
        information["unit pos x"] =  static_cast<int>(x);
        information["unit pos y"] =  static_cast<int>(y);
        information["unit characteristic:\n"+un->characteristic()] = -1;
    }
    else{
        information["no unit on such cell"] = -1;
    }
    return information;
}

map<string, int> FieldCommand::landCelllInfo()
{
    map<string, int> information;
    unsigned x = static_cast<unsigned>(params.find("infoParams")->second.x);
    unsigned y = static_cast<unsigned>(params.find("infoParams")->second.y);
    Landscape* land = field->getCell(x, y)->getLandscape();
    if(land){
        information["land cell pos x"] =  static_cast<int>(x);
        information["land cell pos y"] =  static_cast<int>(y);
        information["landscape type:"] = field->getCell(x, y)->getLandscape()->getLandscapeTypeEnum();
    }
    else{
        information["error with land type"] = 0;
    }
    return information;
}



map<string, int> FieldCommand::neutralFind()
{
    map<string, int> information;
    if(!neutral){
        information["neutral can't be null"] = 0;
        return information;
    }
    for(unsigned i = 0; i < field->getWidth(); i++){
        for(unsigned j = 0; j < field->getHeight(); j++){
            if(field->getCell(i, j)->getNeutral() == neutral){
                information["pos x"] = static_cast<int>(i);
                information["pos y"] = static_cast<int>(j);
            }
        }
    }
    if(information.empty()){
        information["no such neutral el"] = 0;
    }
    return information;

}

map<string, int> FieldCommand::unitFind()
{
    map<string, int> information;
    if(!unit){
        information["unit can't be null"] = 0;
        return information;
    }
    for(unsigned i = 0; i < field->getWidth(); i++){
        for(unsigned j = 0; j < field->getHeight(); j++){
            if(field->getCell(i, j)->getUnit() == unit){
                information["pos x"] = static_cast<int>(i);
                information["pos y"] = static_cast<int>(j);
            }
        }
    }
    if(information.empty()){
        information["no such unitl el"] = -1;
    }
    return information;
}

map<string, int> FieldCommand::unitMove()
{
    map<string, int> information;
    Unit* u = findItem();
    try{
        int x = params.find("move")->second.x;
        int y = params.find("move")->second.y;
        u->move(x, y);
        information["move unit name: "] = u->getTypeEnum();
        information["for pos x: "] = x;
        information["for pos y: "] = y;
    }catch(out_of_range& e){
        information[e.what()]=0;
    }catch(invalid_argument& e){
        information[e.what()]=0;
    }
    return information;
}

Unit *FieldCommand::findItem()
{
    unsigned x = static_cast<unsigned>(params.find("pos")->second.x);
    unsigned y = static_cast<unsigned>(params.find("pos")->second.y);
    return field->getCell(x, y)->getUnit();
}

map<string, int> FieldCommand::noSuchAct()
{
    map<string, int> information;
    information["no such action"] = 0;
    return information;
}

FieldCommand::FieldCommand(PlayingField *field, Actions act, map<string, Data> param)
{
    this->field = field;
    action = act;
    params = param;
    unit = nullptr;
    neutral = nullptr;
}


FieldCommand::FieldCommand(PlayingField *field, Actions act, map<string, Data> param, Unit *u, NeutralObj *n)
{
    this->field = field;
    action = act;
    params = param;
    unit = u;
    neutral = n;
}

map<string, int> FieldCommand::mainInfoAboutObj()
{
    if(action == LAND_INFO){
        return landscapeInfo();
    }else if(action == NEUTRALS_INFO){
        return neutralslInfo();
    }else if(action == UNITS_INFO){
        return unitsInfo();
    }else if(action == NEUTRAL_FIND){
        return neutralFind();
    }else if(action == UNIT_FIND){
        return unitFind();
    }else if(action == MOVE){
        return unitMove();
    }else if(action == UNIT_INFO){
        return unitlInfo();
    }else if(action == LAND_CELL){
        return landCelllInfo();
    }else if(action == NEUTRAL_INFO){
        return neutrallInfo();
    }else{
        return noSuchAct();
    }
}
