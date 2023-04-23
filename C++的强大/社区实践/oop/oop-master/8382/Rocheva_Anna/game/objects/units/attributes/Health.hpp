#ifndef LABOOP_HEALTH_HPP
#define LABOOP_HEALTH_HPP


#include "Attribute.hpp"

class Health : public Attribute{
public:
    explicit Health(int val) : Attribute(val) {};
};


#endif //LABOOP_HEALTH_HPP
