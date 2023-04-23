#include "Field.h"
#include "CheckTail.h"
#include "RemoveCheckTail.h"
#include "UnitFactory.h"
#include "MUCTail.h"
#include "GameBase.h"
#include "Commands.h"
#include "Game.h"
#include <map>
#include "my_exceptions.h"

struct Dialog
{
private:
	void speakAboutUnits();
	void speakAboutBase();
	void showField();
	void speakAboutSave();
	void speakAboutLoad();

	void createUnit();
	void moveUnit(Point p);
	void unitWantToAttack(Point from);
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
	std::vector<std::string> ruleCommands;
	
	Field fld;
	GameBase base;

	std::shared_ptr<AddCheckTail> addTail;
	std::shared_ptr<RemoveCheckTail> removeTail;
	std::shared_ptr<MUCTail> mucTail;

	std::map<char, std::string> d;
//	std::shared_ptr<std::ostream> logOut;
//	LogProxy log;

	std::shared_ptr<AddingCommand> addCommand;
	std::shared_ptr<MovingCommand> moveCommand;
	std::shared_ptr<AttackicngCommand> attackCommand;
	std::shared_ptr<NotifyCommand> notifyCommand;

	std::vector<SaveFile> files;
};