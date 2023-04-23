#ifndef LANDSCAPEPROTECTED_H
#define LANDSCAPEPROTECTED_H
#include <string>

class LandscapeProtected
{
public:
    bool canStand() const
    {
        return true;
    }
    bool cantStand() const
    {
        return false;
    }
};

#endif // LANDSCAPEPROTECTED_H
