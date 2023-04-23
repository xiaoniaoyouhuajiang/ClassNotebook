#ifndef LABOOP_TRAININGBASE_HPP
#define LABOOP_TRAININGBASE_HPP


#include "NeutralObject.hpp"

class TrainingBase : public NeutralObject{
public:
    TrainingBase(){setName('T'); setObjName(TRAIN);};
};

#endif //LABOOP_TRAININGBASE_HPP
