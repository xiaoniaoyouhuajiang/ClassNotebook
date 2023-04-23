#ifndef LAB2_ABSTRACTNEUTRALOBJECT_H
#define LAB2_ABSTRACTNEUTRALOBJECT_H


class AbstractNeutralObject {
public:
    virtual int get_health() const = 0;
    virtual int get_attack() const = 0;
    virtual int get_intelligence() const = 0;
    virtual ~AbstractNeutralObject() {}
};


#endif
