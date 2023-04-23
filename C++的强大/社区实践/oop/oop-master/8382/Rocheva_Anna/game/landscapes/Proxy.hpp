#ifndef LABOOP_PROXY_HPP
#define LABOOP_PROXY_HPP

#include "Grass.hpp"
#include "Forest.hpp"
#include "Mountains.hpp"
#include "Swamp.hpp"

class Proxy : public Landscape{
public:
    explicit Proxy(Land land);
    void changeAttribute(Unit *unit) override;
    char getName() final {};
    Land getLandName() final {};
private:
    Landscape *landscape;
};


#endif //LABOOP_PROXY_HPP
