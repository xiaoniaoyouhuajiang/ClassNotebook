#include "controller.h"
#include "model.h"
#include "coordinate.h"
#include "basehandler.h"
#include <iostream>
#include "derivedhandlers.h"
#include <memory>
#include "handlerregistry.h"
Controller::Controller(){
    //init();
}
void Controller::addHandler(std::size_t type)
{
    myModel.add(HandlerRegistry::getInstance().getByTypeId(type));
}

void Controller::connect(std::size_t id1, std::size_t slot, std::size_t id2){
    myModel.connectById(id1,slot,id2);
}

void Controller::setInput(std::size_t id){
    myModel.setInput(myModel.getHandlerById(id));
}

void Controller::setOutput(std::size_t id){
    myModel.setOutput(myModel.getHandlerById(id));
}

void Controller::deleteHandler(std::size_t id){
    myModel.remove(myModel.getHandlerById(id));
}

void Controller::init(){
    //auto h1 = myModel.add(new CoordinateMakingHandler);
    auto h1 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_COOR_MAKING));
    auto h2 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_DISTRIBUTE));
    auto h3 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_DISTANCE));
    auto h4 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_COOR_BREAKUP));
    auto h5 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_SQUARED));
    auto h6 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_SUM));
    auto h7 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_ROUND2));
    auto h8 = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_DIV_MOD));

    auto h6_dup = myModel.add(HandlerRegistry::getInstance().getByTypeId(HandlerRegistry::TYPE_SUM));
    h6_dup->isOutput = true;

    h1->setNext(0,h2);

    h2->setNext(0,h3);
    h2->setNext(1,h4);

    h3->setNext(0,h5);

    h4->setNext(0,h6);
    h4->setNext(1,h6);

    h5->setNext(0,h7);

    h6->setNext(0,h7);

    h7->setNext(0,h8);

    h7->setNext(1,h8);

    myModel.isOutput = true;
    myModel.setInput(dynamic_cast<Unit*>(h1.get()));
    myModel.setOutput(dynamic_cast<Unit*>(h8.get()));


}

std::vector<std::size_t> Controller::getUnitIds(){
    return myModel.getUnitIds();
//    std::vector<std::size_t> ids;
//    for(std::shared_ptr<Unit> &h : myModel.getManagedHandlers()){
//            ids.push_back(h->id);
//    }
//    return std::vector<std::size_t>(ids);
}

std::vector<std::pair<std::size_t,std::size_t>> Controller::getConnections()
{
//    std::vector<std::pair<std::size_t,std::size_t>> connections;
//    for(std::shared_ptr<Unit> &h : myModel.getManagedHandlers()){
//        for(auto &nxt : h->getNexts()){
//            connections.push_back(std::pair<std::size_t,std::size_t>(h->id,nxt));
//        }
//    }
//    return std::vector<std::pair<std::size_t,std::size_t>>(connections);
    return myModel.getConnections();
}

void Controller::replace(std::size_t id1, std::size_t id2){
    Unit* unit1 = nullptr;
    Unit* unit2 = nullptr;
    for(std::shared_ptr<Unit> &h : myModel.getManagedHandlers()){
        if(h->id==id1) unit1 = h.get();
        if(h->id==id2) unit2 = h.get();
    }
    if(unit1!=nullptr&&unit2!=nullptr){
        switch(unit1->type){
        case HandlerRegistry::TYPE_SUM:
        case HandlerRegistry::TYPE_SQUARED:
            myModel.replace<double,double>(unit1,unit2);
            break;
        case HandlerRegistry::TYPE_DIV_MOD:
            myModel.replace<int,int>(unit1,unit2);
            break;
        case HandlerRegistry::TYPE_DISTRIBUTE:
            myModel.replace<Coordinate, double>(unit1,unit2);
            break;
        case HandlerRegistry::TYPE_COOR_BREAKUP:
        case HandlerRegistry::TYPE_DISTANCE:
            myModel.replace<Coordinate, double>(unit1,unit2);
            break;
        case HandlerRegistry::TYPE_COOR_MAKING:
            myModel.replace<double, Coordinate>(unit1,unit2);
            break;
        case HandlerRegistry::TYPE_ROUND2:
            myModel.replace<double, int>(unit1,unit2);
            break;
        default:
            throw TypeException();

        }
    }


}

void Controller::backup(){
    myModel.backup();
}

void Controller::handle(double c1,double c2){
    myModel.backup();
    double *arr = new double[2];
    arr[0] = c1;
    arr[1] = c2;
    myModel.handle(2,arr);
//        myModel.handle(c1);
//        myModel.handle(c2);
}

void Controller::undo(){
    myModel.undo();
}
std::string Controller::getModelState(){
    return myModel.toString();
}
std::map<std::size_t,std::string> Controller::getHandlersInfo(){
    std::map<std::size_t,std::string> result;
    for(std::shared_ptr<Unit> h : myModel.getManagedHandlers()){
        //std::cout<<h->toString();
        result.insert(std::pair<std::size_t,std::string>(h->id,h.get()->toString()));
    }
    return result;
}

void Controller::loadFromTextFile(std::string path){
    myModel.loadFromFile<TxtReader>(path);
}

void Controller::loadFromBinFile(std::string path){
    myModel.loadFromFile<BinaryReader>(path);
}

void Controller::saveToTextFile(std::string path){
    myModel.saveToFile<TxtWriter>(path);
}

void Controller::saveToBinFile(std::string path){
    myModel.saveToFile<BinaryWriter>(path);
}
