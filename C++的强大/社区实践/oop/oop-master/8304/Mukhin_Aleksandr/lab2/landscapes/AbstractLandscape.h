#ifndef LAB2_ABSTRACTLANDSCAPE_H
#define LAB2_ABSTRACTLANDSCAPE_H


class AbstractLandscape {
public:
    virtual int get_health() const = 0;
    virtual int get_attack() const = 0;
    virtual int get_intelligence() const = 0;
    virtual ~AbstractLandscape() {};
};


#endif
