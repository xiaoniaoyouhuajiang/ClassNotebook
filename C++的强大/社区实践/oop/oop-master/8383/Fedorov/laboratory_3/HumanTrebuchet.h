#ifndef HUMANTREBUCHET_H
#define HUMANTREBUCHET_H

#include "TSiegeCharacter.h"

class HumanTrebuchet : public TSiegeCharacter {
    private:
        void initVariables();
    public:
        HumanTrebuchet(const HumanTrebuchet& obj);
        GameObj* copy(GameField* field);
        /* обычная атака */
        HumanTrebuchet(GameField* field, int x, int y);
        virtual ~HumanTrebuchet() {}
 };

#endif // HUMANTREBUCHET_H
