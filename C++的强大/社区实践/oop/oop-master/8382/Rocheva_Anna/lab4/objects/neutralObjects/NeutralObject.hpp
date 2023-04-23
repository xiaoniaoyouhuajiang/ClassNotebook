#ifndef LABOOP_NEUTRALOBJECT_HPP
#define LABOOP_NEUTRALOBJECT_HPP

#include "../Object.hpp"

enum NeutralObjects {BAR, HOSPITAL, SHOP, TRAIN};

class NeutralObject : public Object{
public:
    Coordinates * getCoordinates() final { return coordinates;};
    void setCoordinates(int x, int y) final;
    char getName() final { return name;};
    void setName(char name) {this->name = name;};
    void setObjName(NeutralObjects obName) {objectName = obName;};
    NeutralObjects getObjName() {return objectName;};
private:
    Coordinates *coordinates;
    char name;
    NeutralObjects objectName;
};

#endif //LABOOP_NEUTRALOBJECT_HPP
