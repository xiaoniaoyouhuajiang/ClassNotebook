#ifndef LABOOP_SHOP_HPP
#define LABOOP_SHOP_HPP


#include "NeutralObject.hpp"

class Shop : public NeutralObject{
public:
    Shop(){setName('S'); setObjName(SHOP);};
};

#endif //LABOOP_SHOP_HPP
