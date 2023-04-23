



#ifndef NEW_LR1_KNIGHT_H
#define NEW_LR1_KNIGHT_H


#include "../Warriors.h"

class Knight : public Warriors
{
public:
    Knight() : Warriors(50, 50, 50, 0, 'K'){};
    ~Knight() = default;
};


#endif //NEW_LR1_KNIGHT_H
