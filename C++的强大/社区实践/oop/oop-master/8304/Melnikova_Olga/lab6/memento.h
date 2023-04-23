#include "iostream"
#include "game.h"

class Memento {
 public:
    virtual std::string& state() const = 0;

};
