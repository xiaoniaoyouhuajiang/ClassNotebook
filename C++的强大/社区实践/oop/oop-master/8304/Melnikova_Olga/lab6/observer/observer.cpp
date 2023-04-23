#include "observer.h"
#include "iostream"
//#include "mainwindow.h"

//Observer::Observer() { }

//Observer::Observer(Object* obj) : observingObject(obj) { }

Observer::~Observer() { }

void Observer::update(std::string message) {
    // add some logic here
    std::cout << message << std::endl;
}
