

//

#ifndef NEW_LR1_LANDSCAPEFACTORY_H
#define NEW_LR1_LANDSCAPEFACTORY_H


#include "Field/Field.h"
#include "Forest/Forest.h"
#include "Mountain/Mountain.h"

class LandscapeFactory
{
public:
    LandscapeFactory();
    ~LandscapeFactory();

    Field* getFieldLandscape();
    Forest* getForestLandscape();
    Mountain* getMountainLandscape();
private:
    Field* field_;
    Forest* forest_;
    Mountain* mountain_;
};


#endif //NEW_LR1_LANDSCAPEFACTORY_H
