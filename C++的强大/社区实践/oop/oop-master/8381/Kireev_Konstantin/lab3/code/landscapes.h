#ifndef LANDSCAPES_H
#define LANDSCAPES_H
#include "printInterface.h"

enum LandscapeType {MOUNTAINS, WATER, GROUND};

class LandscapeInterface : public printInterface
{
public:
    virtual ~LandscapeInterface() = default;
    virtual bool canHoldCreature() const = 0;
    virtual LandscapeType getType() = 0;
    virtual LandscapeInterface* copy() = 0;
};

class LandscapeProxy : public LandscapeInterface
{
private:
    LandscapeInterface* landscape;
public:
    LandscapeProxy(LandscapeInterface* landscape)
    {
        this->landscape = landscape;
    }

    bool canHoldCreature() const override
    {
        return landscape->canHoldCreature();
    }

    LandscapeType getType() override
    {
        return landscape->getType();
    }

    QString getClass() override
    {
        return landscape->getClass();
    }

    LandscapeInterface* copy() override
    {
        return new LandscapeProxy(landscape);
    }
};



class Mountains : public LandscapeInterface
{
public:
    bool canHoldCreature() const override
    {
        return true;
    }
    QString getClass() override
    {
        return "^__^^^_^^_";
    }
    LandscapeType getType() override
    {
        return MOUNTAINS;
    }
    LandscapeInterface* copy() override
    {
        return new Mountains();
    }
};


class Ground : public LandscapeInterface
{
public:
    bool canHoldCreature() const override
    {
        return true;
    }
    QString getClass() override
    {
        return "===========";
    }
    LandscapeType getType() override
    {
        return GROUND;
    }
    LandscapeInterface* copy() override
    {
        return new Ground();
    }
};


class Water : public LandscapeInterface
{
public:
    bool canHoldCreature() const override
    {
        return false;
    }
    LandscapeType getType() override
    {
        return WATER;
    }
    QString getClass() override
    {
        return "~~~~~~~~~~~~~";
    }
    LandscapeInterface* copy() override
    {
        return new Water();
    }
};


#endif // LANDSCAPES_H
