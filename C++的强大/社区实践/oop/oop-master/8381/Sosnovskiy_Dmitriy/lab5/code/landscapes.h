#ifndef LANDSCAPES_H
#define LANDSCAPES_H
#include "iprintable.h"
#include "enums.h"

class ILandscape : public IPrintable
{
public:
    virtual ~ILandscape() = default;
    virtual bool canHoldCreature() const = 0;
    virtual LandscapeType getType() = 0;
    virtual ILandscape* copy() = 0;
};

class LandscapeProxy : public ILandscape
{
private:
    ILandscape* landscape;
public:
    LandscapeProxy(ILandscape* landscape)
    {
        this->landscape = landscape;
    }

    bool canHoldCreature() const override
    {
        return landscape->canHoldCreature();
    }

    LandscapeType getType() override { return landscape->getType(); }

    QString getClass() override { return landscape->getClass(); }

    ILandscape* copy() override { return new LandscapeProxy(landscape); }
};

class Mountains : public ILandscape
{
public:
    bool canHoldCreature() const override { return true; }
    QString getClass() override { return "Mountains"; }
    LandscapeType getType() override { return MOUNTAINS; }
    ILandscape* copy() override {
        return new Mountains();
    }
};


class Ground : public ILandscape
{
public:
    bool canHoldCreature() const override { return true; }
    QString getClass() override { return "Ground"; }
    LandscapeType getType() override { return GROUND; }
    ILandscape* copy() override{
        return new Ground();
    }
};


class Water : public ILandscape
{
public:
    bool canHoldCreature() const override { return false; }
    LandscapeType getType() override { return WATER; }
    QString getClass() override { return "Water"; }
    ILandscape* copy() override{
        return new Water();
    }
};


#endif // LANDSCAPES_H
