#include "Saver.h"



void Saver::writeLastCell(int x, int y)
{
	std::shared_ptr<FieldCell> cell = field->getCell(x, y);
	saveLand(cell->getLand());
	saveTower(cell->getTower());
}

void Saver::writeCell(int x, int y)
{
	std::shared_ptr<FieldCell> cell = field->getCell(x, y);
	saveLand(cell->getLand());
	saveUnit(cell->getUnit());
	saveObject(cell->getObj());
}

void Saver::saveLand(std::shared_ptr<Land> land)
{
	file << "L\n";
	switch (land->getType()) {
	case LandType::COMMON_LAND:
		file << 0 << std::endl;
		break;
	case LandType::GRASS_LAND:
		file << 1 << std::endl;
		break;
	case LandType::HILL_LAND:
		file << 2 << std::endl;
		break;
	default:
		break;
    }
}

void Saver::saveTower(std::shared_ptr<Tower> tower)
{
	file << "T\n";
	if (tower != nullptr) {
		file << 1 << std::endl;

		std::shared_ptr<TowerSnapshot> towerSnapshot = tower->getSnapshot();
		file << towerSnapshot->getLevel() << std::endl;
		file << towerSnapshot->getHP() << std::endl;
		file << towerSnapshot->getDamage() << std::endl;
		file << towerSnapshot->getSize() << std::endl;
		file << towerSnapshot->getUnitCount() << std::endl;
        switch(towerSnapshot->getKind()) {
        case Kind::ZOMBY:
            file << 0 << std::endl;
            break;
        case Kind::HUMAN:
            file << 1 << std::endl;
            break;
        }
		switch (towerSnapshot->getFactory()->getType()) {
		case UnitType::BITING_ZOMBY:
			file << 0 << std::endl;
			break;
		case UnitType::HUMAN_ON_BIKE:
			file << 1 << std::endl;
			break;
		case UnitType::HUMAN_ON_CAR:
			file << 2 << std::endl;
			break;
		case UnitType::HUMAN_WITH_BAT:
			file << 3 << std::endl;
			break;
		case UnitType::HUMAN_WITH_GRENADE:
			file << 4 << std::endl;
			break;
		case UnitType::HUMAN_WITH_GUN:
			file << 5 << std::endl;
			break;
		case UnitType::HUMAN_WITH_SWORD:
			file << 6 << std::endl;
			break;
		case UnitType::KAMIKADZE_ZOMBY:
			file << 7 << std::endl;
			break;
		case UnitType::SPIT_TO_AREA_ZOMBY:
			file << 8 << std::endl;
			break;
		case UnitType::SPIT_TO_ENEMY_ZOMBY:
			file << 9 << std::endl;
			break;
		case UnitType::STINKY_ZOMBY:
			file << 10 << std::endl;
			break;
		case UnitType::STRONG_ZOMBY:
			file << 11 << std::endl;
			break;
		default:
			break;
		}
        file << towerSnapshot->getX() << std::endl;
        file << towerSnapshot->getY() << std::endl;
	}
	else {
		file << -1 << std::endl;
	}
}

void Saver::saveUnit(std::shared_ptr<Unit> unit)
{
	file << "U\n";
	if (unit != nullptr) {
		file << 1 << std::endl;
		std::shared_ptr<UnitSnapshot> unitSnapshot = unit->getSnapshot();
		switch (unitSnapshot->getType()) {
		case UnitType::BITING_ZOMBY:
			file << 0 << std::endl;
			break;
		case UnitType::HUMAN_ON_BIKE:
			file << 1 << std::endl;
			break;
		case UnitType::HUMAN_ON_CAR:
			file << 2 << std::endl;
			break;
		case UnitType::HUMAN_WITH_BAT:
			file << 3 << std::endl;
			break;
		case UnitType::HUMAN_WITH_GRENADE:
			file << 4 << std::endl;
			break;
		case UnitType::HUMAN_WITH_GUN:
			file << 5 << std::endl;
			break;
		case UnitType::HUMAN_WITH_SWORD:
			file << 6 << std::endl;
			break;
		case UnitType::KAMIKADZE_ZOMBY:
			file << 7 << std::endl;
			break;
		case UnitType::SPIT_TO_AREA_ZOMBY:
			file << 8 << std::endl;
			break;
		case UnitType::SPIT_TO_ENEMY_ZOMBY:
			file << 9 << std::endl;
			break;
		case UnitType::STINKY_ZOMBY:
			file << 10 << std::endl;
			break;
		case UnitType::STRONG_ZOMBY:
			file << 11 << std::endl;
			break;
		default:
			break;
		}
		file << unitSnapshot->getHP() << std::endl;
		file << unitSnapshot->getMaxHP() << std::endl;
		file << unitSnapshot->getOwnArmor() << std::endl;
		file << unitSnapshot->getOwnDamage() << std::endl;
		if (unitSnapshot->getVisability()) {
			file << 1 << std::endl;
		}
		else {
			file << 0 << std::endl;
		}
		file << unitSnapshot->getLevel() << std::endl;
		file << unitSnapshot->getLandDamage() << std::endl;
		file << unitSnapshot->getLandDefence() << std::endl;
		file << unitSnapshot->getObserverSize() << std::endl;
		file << unitSnapshot->getObserverCount() << std::endl;
		file << unitSnapshot->getCoordX() << std::endl;
		file << unitSnapshot->getCoordY() << std::endl;
        file << unitSnapshot->getLastStep() << std::endl;
		std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers = unitSnapshot->getObservers();
		for (int i = 0; i < unitSnapshot->getObserverSize(); i++) {
			if (observers[i] != nullptr) {
				file << observers[i]->getX() << std::endl;
				file << observers[i]->getY() << std::endl;
			}
		}

	}
	else {
		file << -1 << std::endl;
	}
}

void Saver::saveObject(std::shared_ptr<NeutralObject> object)
{
	file << "O\n";
	if (object != nullptr) {
		file << 1 << std::endl;
		std::shared_ptr<ObjectSnapshot> objectSnapshot = object->getSnapshot();
		switch (objectSnapshot->getType()) {
		case ObjectType::LARGE_ARMOR_OBJECT:
			file << 0 << std::endl;
			break;
		case ObjectType::LARGE_MEDICINE:
			file << 1 << std::endl;
			break;
		case ObjectType::SMALL_ARMOR:
			file << 2 << std::endl;
			break;
		case ObjectType::SMALL_MEDICINE:
			file << 3 << std::endl;
			break;
		default:
			break;
		}
	}
	else {
		file << -1 << std::endl;
	}
}

Saver::Saver(GameMode mode, size_t stepNumber, std::shared_ptr<Field> field, std::shared_ptr<State> state) : mode(mode), stepNumber(stepNumber), field(field), state(state)
{
	file.open("lastSave.txt");
}


Saver::~Saver()
{
	file.close();
}

void Saver::save() {
    saveModeAndNumber();
    saveField();
    saveState();
}


void Saver::saveField() {
    file << field->getWidth() << std::endl;
    file << field->getHeight() << std::endl;
    for (int j = 0; j < field->getWidth(); j++) {
        writeLastCell(j, 0);
    }
    for (int j = 0; j < field->getWidth(); j++) {
        writeLastCell(j, field->getHeight() - 1);
    }
    for (int  i = 1; i < field->getHeight() - 1; i++) {
        for (int j = 0; j < field->getWidth(); j++) {
            writeCell(j, i);
        }
    }
}


void Saver::saveModeAndNumber() {
    if (mode == GameMode::SOLO_GAME) {
        file << 1 << std::endl;
    }
    else {
        file << 2 << std::endl;
    }
    file << stepNumber << std::endl;
}


void Saver::saveState() {
    switch (state->getType()) {
    case StateType::TOWER_SETTING_STATE:
        file << 0 << std::endl;
        break;
    case StateType::UNIT_SETTING_STATE:
        file << 1 << std::endl;
        break;
    }
    switch (state->getKind()) {
    case Kind::ZOMBY:
        file << 0 << std::endl;
        break;
    case Kind::HUMAN:
        file << 1 << std::endl;
        break;
    }
    file << state->getResources();
}
