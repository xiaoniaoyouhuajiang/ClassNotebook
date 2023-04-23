#ifndef OOP_LANDSCAPEPROXY_H
#define OOP_LANDSCAPEPROXY_H

#include "Mountains.h"
#include "Fog.h"
#include "Desert.h"
#include <map>
class LandscapeProxy : public Landscape{
public:
    LandscapeInfo interaction(LandscapeTypes type) override;
private:
    Mountains mountains;
    Desert desert;
    Fog fog;
    std::map<LandscapeTypes, LandscapeInfo> dict;
};


#endif //OOP_LANDSCAPEPROXY_H
