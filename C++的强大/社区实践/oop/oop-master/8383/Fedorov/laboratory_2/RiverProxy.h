#ifndef RIVERPROXY_H
#define RIVERPROXY_H
#include "TerrainProxy.h"



class RiverProxy : public TerrainProxy{
    public:
        int getMovementCost() override;
        bool isMovement() override;
        void affect() override {}
        void open() override;
        bool addObj(Obj obj_) override;
        RiverProxy(int x, int y, bool open_ = false);
        virtual ~RiverProxy();
};
#endif // RIVERPROXY_H
