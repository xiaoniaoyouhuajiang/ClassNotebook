#ifndef ITERRAIN_H
#define ITERRAIN_H
class GameObj;
class Unit;
typedef GameObj* Obj;

class ITerrain
{
public:
    virtual int getMovementCost() = 0;
    virtual bool isMovement() = 0;
    virtual void affect() = 0;
    virtual void open() = 0;
    virtual void removeObj() = 0;
    virtual Obj getObj() = 0;
    virtual bool addObj(Obj obj_) = 0;
    virtual int getAnimation() = 0;
    virtual Unit* getUnit() = 0;
    //virtual void close() = 0;
    //virtual void update() = 0;
  //virtual void copy(Terrain& other, GameField* field) = 0;
};



#endif // ITERRAIN_H
