#ifndef PORTAL_H
#define PORTAL_H

#include "INeutralObj.h"

class Portal : public INeutralObj
{
private:
    struct NextPlace{
        int newX;
        int newY;
        /* ... */
    };

    NextPlace* nextPlace;
public:
    void addPlace(int x, int y);
    void updateState() override;
    Portal(GameField* field, int x, int y);
    friend Unit& operator+=(Unit& left, const Portal& right);
    virtual ~Portal();
};

#endif // PORTAL_H
