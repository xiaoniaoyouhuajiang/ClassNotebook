#include "handlerregistry.h"

//static const std::size_t TYPE_SUM = 0;
//static const std::size_t TYPE_DISTRIBUTE = 1;
//static const std::size_t TYPE_SQUARED = 2;
//static const std::size_t TYPE_DIV_MOD = 3;
//static const std::size_t TYPE_ROUND = 4;
//static const std::size_t TYPE_DISTANCE = 5;
//static const std::size_t TYPE_COOR_MAKING = 6;
//static const std::size_t TYPE_COOR_BREAKUP = 7;

HandlerRegistry* HandlerRegistry::instance = nullptr;
HandlerRegistry::HandlerRegistry()
{
    handlers.insert(std::pair<std::string,Unit*>("CoordinateMaking",new CoordinateMakingHandler));
    handlers.insert(std::pair<std::string,Unit*>("Distribute",new DistributeHandler));
    handlers.insert(std::pair<std::string,Unit*>("Distance",new DistanceHandler));
    handlers.insert(std::pair<std::string,Unit*>("CoordinateBreakUp",new CoordinateBreakUpHandler));
    handlers.insert(std::pair<std::string,Unit*>("Squared",new SquaredHandler));
    handlers.insert(std::pair<std::string,Unit*>("Sum",new SumHandler));
    handlers.insert(std::pair<std::string,Unit*>("Round2",new RoundHandler2));
    handlers.insert(std::pair<std::string,Unit*>("DivMod",new DivModHandler));
    handlers.insert(std::pair<std::string,Unit*>("Round1",new RoundHandler1));
    handlers.insert(std::pair<std::string,Unit*>("DistributeD",new DistributeHandlerD));
}

Unit* HandlerRegistry::getByTypeId(std::size_t type){
    Unit* clone = nullptr;
    switch(type){
    case TYPE_SUM:
        clone = handlers["Sum"]->clone();
        break;
    case TYPE_DISTRIBUTE:
        clone = handlers["Distribute"]->clone();
        break;
    case TYPE_SQUARED:
        clone = handlers["Squared"]->clone();
        break;
    case TYPE_DIV_MOD:
        clone = handlers["DivMod"]->clone();
        break;
    case TYPE_ROUND2:
        clone = handlers["Round2"]->clone();
        break;
    case TYPE_DISTANCE:
        clone = handlers["Distance"]->clone();
        break;
    case TYPE_COOR_MAKING:
        clone = handlers["CoordinateMaking"]->clone();
        break;
    case TYPE_COOR_BREAKUP:
        clone = handlers["CoordinateBreakUp"]->clone();
        break;
    case TYPE_ROUND1:
        clone = handlers["Round1"]->clone();
        break;
    case TYPE_DISTRIBUTE_D:
        clone = handlers["DistributeD"]->clone();
        break;
    default: clone = nullptr;
    }

    if(clone!=nullptr) clone->type = type;
    return clone;
}

std::string HandlerRegistry::getTypeDescription(std::size_t type){
    switch(type){
    case TYPE_SUM:
        return "(double)a; (double)b -> (double)a+b";
    case TYPE_DISTRIBUTE:
        return "(Coordinate)(a,b) -> (Coordinate)(a,b); (Coordinate)(a,b)";
    case TYPE_SQUARED:
        return "(double)a -> (double)a^2";
    case TYPE_DIV_MOD:
        return "(int)a; (int)b -> (int)a/b; (int)a%b";
    case TYPE_ROUND2:
        return "(double)a; (double)b -> (int)[a]; (int)[b]";
    case TYPE_DISTANCE:
        return "(Coordinate)(a,b) -> (double)sqrt(a^2+b^2)";
    case TYPE_COOR_MAKING:
        return "(double)a; (double)b -> (Coordinate)(a,b)";
    case TYPE_COOR_BREAKUP:
        return "(Coordinate)(a,b) -> (double)a; (double)b";
    case TYPE_ROUND1:
        return "(double)a -> (int)[a]";
    case TYPE_DISTRIBUTE_D:
        return "(double)a -> (double)a; (double)a";
    default: return "";
    }
}

