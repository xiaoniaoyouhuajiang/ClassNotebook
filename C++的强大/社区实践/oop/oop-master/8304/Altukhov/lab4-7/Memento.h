#pragma once
#include "Base.h"
#include "Field.h"
#include "Unit.h"
//#include "Terrain.h"
class Memento;


class Memento
{

public:

	int whatPlayerTurn;

	////FIELD
	int fieldW, fieldH;
	//enum class TerrainTypes {
	//	FIELD, FOREST, SWAMP
	//};
	//enum class NeutralObjectTypes {
	//	NONE, TOWER, WEAPONRY, CANNON, SHRINE
	//};
	struct TileInfo {
		int x, y;
		int type;
		int typeNeutral;
		int capturedBy;
	};
	std::vector<TileInfo> tiles;

	////BASE1
	int hp1, money1, turn1;
	//enum class UnitTypes {
	//	MELEE, RANGE, HORSEMAN
	//};
	struct UnitInfo {
		int x, y;
		int type;
		int level;
		int hp;
		int canMove;
		int canAttack;
		//int attackDebuff;
		//int armorBuff;
		//int attackBuff;
		//int rangeBuff;

	};
	std::vector<UnitInfo> units1;


	////BASE2
	int hp2, money2, turn2;
	std::vector<UnitInfo> units2;






	void getInfoFromBase(Base* base, bool myTurn = false);
	void getInfoFromField(Field* field);
	void saveToFile(std::string& fileName);
	bool loadFromFile(Field* field, Base* myBase, Base* otherBase, std::string& fileName);
	void loadInfoToBase(Base* base, int num);
	void loadInfoToField(Field* field);

};

