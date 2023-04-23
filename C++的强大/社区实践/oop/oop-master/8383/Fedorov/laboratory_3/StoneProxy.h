#ifndef STONEPROXY_H
#define STONEPROXY_H
#include "TerrainProxy.h"


class StoneProxy : public TerrainProxy{
    public:
        int getMovementCost() override;
        bool isMovement() override;
        void affect() override {}
        void open() override;
        Obj getObj() override;
        bool addObj(Obj obj_) override;
        StoneProxy(int x, int y, bool open_ = false);
        virtual ~StoneProxy();
};

#endif // STONEPROXY_H
