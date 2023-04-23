#ifndef LABOOP_FACADE_HPP
#define LABOOP_FACADE_HPP

#include "Manager.hpp"

class Facade {
public:
    explicit Facade(){manager = new Manager;};
    void startGame();
    void makeAction();
    void createGamer();
    ~Facade() {delete manager;};
protected:
    Manager *manager;
};


#endif //LABOOP_FACADE_HPP
