#include "Field.h"
#include "CheckTail.h"
#include "RemoveCheckTail.h"
#include "UnitFactory.h"
#include "MUCTail.h"

struct Dialog
{
private:
	void speakAboutUnits();
	void speakAboutBase();
	void showField();

	void createFiledUnit();
	void removeFieldUnit();
	void moveFieldUnit();
	void characteristicFieldUnit();

	void createBaseUnit();
	void setMaxUnitsCntToBase();

	void writeUnitsLegend();
	bool addBase(Point p);

public:
	Dialog();
	void speak();

private:
	std::vector<std::string> startCommands;
	std::vector<std::string> unitCommands;
	std::vector<std::string> baseCommands;
	
	Field fld;

	std::shared_ptr<AddCheckTail> addTail;
	std::shared_ptr<RemoveCheckTail> removeTail;
	std::shared_ptr<MUCTail> mucTail;
	

};