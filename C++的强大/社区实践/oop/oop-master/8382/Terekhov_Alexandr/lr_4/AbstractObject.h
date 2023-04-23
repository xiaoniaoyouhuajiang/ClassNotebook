#ifndef OOP_ABSTRACTOBJECT_H
#define OOP_ABSTRACTOBJECT_H

class AbstractObject {
protected:
    char pict;
public:
    AbstractObject(char pict):pict{pict}{}
    char getPict() const { return pict; }
};

#endif //OOP_ABSTRACTOBJECT_H