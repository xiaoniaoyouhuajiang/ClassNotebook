#ifndef LABS_UNITCREATOR_H
#define LABS_UNITCREATOR_H

#include "../Units/Unit.h"
#include "../Units/Priest.h"
#include "../Units/Necromancer.h"
#include "../Units/Katanadude.h"
#include "../Units/Yoyoist.h"
#include "../Units/Crossbow.h"
#include "../Units/Slingerman.h"
#include <iostream>
class Creator {  // абстрактный метод
    virtual Unit* create(int x, int y) = 0;
};

class NecroCreator : public Creator {
public:
    Unit* create(int x, int y) {
        return new Necromancer(x,y);
    }
};

class PriestCreator : public Creator {
public:
    Unit* create(int x, int y) {
        return new Priest(x,y);
    }
};

class KatanaCreator : public Creator {
public:
    Unit* create(int x, int y) {
        return new Katana(x,y);
    }
};

class YoyoCreator : public Creator {
public:
    Unit* create(int x, int y) {
        return new Yoyoist(x,y);
    }
};

class CrossbowCreator : public Creator {
public:
    Unit* create(int x, int y) {
        return new Crossbow(x,y);
    }
};

class SlingermanCreator : public Creator {
public:
    Unit* create(int x, int y) {
        return new Slingerman(x,y);
    }
};

#endif //LABS_UNITCREATOR_H
