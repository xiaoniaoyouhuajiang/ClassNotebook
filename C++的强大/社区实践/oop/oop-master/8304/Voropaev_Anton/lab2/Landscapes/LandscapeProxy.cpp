#include "LandscapeProxy.h"


LandscapeInfo LandscapeProxy::interaction(LandscapeTypes type) {

    if(dict.find(type) != dict.end()) {
        return dict[type];
    }

    LandscapeInfo effect;
    switch(type){
        case LandscapeTypes::Mountain :
            effect = mountains.interaction(type);
            break;
        case LandscapeTypes::Fog :
            effect = fog.interaction(type);
            break;
        case LandscapeTypes::Desert :
            effect = desert.interaction(type);
            break;
        default:
            break;
    }
    dict[type] = effect;
    return effect;
}
