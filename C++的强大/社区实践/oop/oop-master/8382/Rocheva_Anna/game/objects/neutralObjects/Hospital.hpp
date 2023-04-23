#ifndef LABOOP_HOSPITAL_HPP
#define LABOOP_HOSPITAL_HPP

#include "NeutralObject.hpp"

class Hospital : public NeutralObject{
public:
    Hospital() {setName('H'); setObjName(HOSPITAL);};
};

#endif //LABOOP_HOSPITAL_HPP
