#ifndef LANDSCAPES_H
#define LANDSCAPES_H
#include "printInterface.h"

class LandscapeInterface : public printInterface
{
public:
    virtual ~LandscapeInterface() = default;
    virtual bool interaction() const = 0;
    virtual LandscapeInterface* copy() = 0;
};

class Proxy : public LandscapeInterface
{
private:
    LandscapeInterface* landscape;

public:
    Proxy(LandscapeInterface* landscape)
    {
        this->landscape = landscape;
    }

    bool interaction() const override
    {
        return landscape->interaction();
    }

    QString getClass() override
    {
        return landscape->getClass();
    }

    LandscapeInterface* copy() override
    {
        return new Proxy(landscape);
    }
};



class Mountains : public LandscapeInterface
{
public:
    bool interaction() const override
    {
        return false;
    }

    QString getClass() override
    {
        return "^_^^^_^_^^_";
    }

    LandscapeInterface* copy() override
    {
        return new Mountains();
    }
};


class Water : public LandscapeInterface
{
public:
    bool interaction() const override
    {
        return false;
    }

    QString getClass() override
    {
        return "~~~~~~~~~~~";
    }

    LandscapeInterface* copy() override
    {
        return new Water();
    }
};


class Ground : public LandscapeInterface
{
public:
    bool interaction() const override
    {
        return true;
    }

    QString getClass() override
    {
        return "==========";
    }

    LandscapeInterface* copy() override
    {
        return new Ground();
    }
};

#endif // LANDSCAPES_H
