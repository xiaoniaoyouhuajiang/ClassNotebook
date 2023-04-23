#ifndef GAMEFIELD_H
#define GAMEFIELD_H




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
public:
  int** gridView;
  void openArround(int, int);
  GameField(int,int);
  bool move(Unit* unit, int x, int y);
  void addObj(Obj);
  int getWidth();
  int getHeight();
  void update();
  void createMap();
  void deleteObj(Obj);
  virtual ~GameField();
};

#endif // GAMEFIELD_H

