#ifndef originator_hpp
#define originator_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "concretememento.hpp"
#include "position2d.hpp"

class PlayGame;

struct UnitStateSnap
{
    std::string unitName;
    double healthPoints;
    Position2D position;
};


class Originator
{
private:
    std::string filePath;
    
public:
    Originator(std::string filePath);
    ~Originator(){}
    
    void doSomething(const PlayGame& playGame);
     std::shared_ptr<Memento> Save(const PlayGame& playGame) {
      doSomething(playGame);
      return std::make_shared<ConcreteMemento>(ConcreteMemento(filePath));
    }
    void Restore(PlayGame& playGame);
};
#endif /* originator_hpp */
