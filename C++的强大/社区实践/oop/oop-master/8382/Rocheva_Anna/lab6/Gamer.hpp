#ifndef LABOOP_GAMER_HPP
#define LABOOP_GAMER_HPP

#include "objects/Base.hpp"
#include <string>
#include <utility>

class Gamer {
public:
    explicit Gamer(std::string name) : name(std::move(name)) {};
    std::string getGamerName() {return name;};
private:
    std::string name;
};


#endif //LABOOP_GAMER_HPP
