#include "Field.h"
#include "CheckTail.h"
#include "RemoveCheckTail.h"
#include "UnitFactory.h"
#include "MUCTail.h"
#include "GameBase.h"
#include "Log.h"
#include <map>

struct Dialog
{
private:
	void speakAboutUnits();
	void speakAboutBase();
	void showField();

	void createUnit();
	void moveUnit();
	void unitWantToAttack();
	void unitChill();

	void writeUnitsLegend();
	void tellUnitCharacteristics();

public:
	Dialog();
	void speak();

private:
	std::vector<std::string> startCommands;
	std::vector<std::string> unitCommands;
	std::vector<std::string> baseCommands;
	std::vector<std::string> logCommands;
	
	Field fld;
	GameBase base;

	std::shared_ptr<AddCheckTail> addTail;
	std::shared_ptr<RemoveCheckTail> removeTail;
	std::shared_ptr<MUCTail> mucTail;

	std::map<char, std::string> d;
	LogProxy log;
	std::shared_ptr<std::ostream> logOut;

};