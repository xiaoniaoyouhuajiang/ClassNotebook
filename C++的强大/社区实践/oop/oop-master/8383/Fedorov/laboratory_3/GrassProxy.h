#ifndef GRASSPROXY_H
#define GRASSPROXY_H

#include "TerrainProxy.h"


class GrassProxy : public TerrainProxy{
    public:
        int getMovementCost() override;
        bool isMovement() override;
        void open() override;
        bool addObj(Obj obj_) override;
        GrassProxy(int x, int y, bool open_ = false);
        virtual ~GrassProxy();
};

#endif // GRASSPROXY_H
