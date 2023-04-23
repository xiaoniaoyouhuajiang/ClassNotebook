#ifndef GAMEFIELD_H
#define GAMEFIELD_H
class IMediator;
class GameObj;
class Unit;
class TerrainProxy;
typedef TerrainProxy* pTerrain;
typedef GameObj* Obj;

class GameField
{
private:
  int width_;
  int height_;
  pTerrain** gridLogic;
  int countObj;
  void initialise();
  IMediator* attackMediator;
public:
  int** gridView;
  void openArround(int, int);
  GameField(int,int);
  bool move(Unit* unit, int x, int y);
  void addObj(Obj);
  int getWidth();
  int getHeight();
  Obj getObj(int x, int y);
  //Unit* getUnit();
  void update();
  void createMap();
  void deleteObj(Obj);
  void deleteObj(int x, int y);
  int getDistant(int x1, int y1, int x2, int y2);
  virtual ~GameField();
};

#endif // GAMEFIELD_H

