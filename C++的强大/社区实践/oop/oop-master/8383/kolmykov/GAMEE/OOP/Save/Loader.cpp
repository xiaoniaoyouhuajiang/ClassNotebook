#include "Loader.h"



void Loader::setLastCell(int x, int y)
{
	std::shared_ptr<FieldCell> cell = field->getCell(x, y);
	cell->setLand(getLand());
	cell->setTower(getTower());
}

void Loader::setCell(int x, int y)
{
	std::shared_ptr<FieldCell> cell = field->getCell(x, y);
	cell->setLand(getLand());
	cell->setUnit(getUnit());
	cell->setObj(getObj());
}

std::shared_ptr<Land> Loader::getLand()
{
	std::string symb;
	file >> symb;
	if (symb == "L") {
		int type;
		file >> type;
		switch (type) {
		case 0:
			return std::shared_ptr<Land>(new CommonLand());
		case 1:
			return std::shared_ptr<Land>(new GrassLand());
		case 2:
			return std::shared_ptr<Land>(new HillLand());
		default:
			std::cout << "Incorrect save file\n";
			return nullptr;
		}
	}
	else {
		std::cout << "Incorrect save file\n";
		return nullptr;
	}
}

std::shared_ptr<Tower> Loader::getTower()
{
	std::string symb;
	file >> symb;
	if (symb == "T") {
		int isExist;
		file >> isExist;
		if (isExist == 1) {
			int level;
			file >> level;
			int hp;
			file >> hp;
			int damage;
			file >> damage;
			int size;
			file >> size;
			int unitCount;
			file >> unitCount;
            int kindI;
            Kind kind;
            file >> kindI;
            switch (kindI) {
            case 0:
                kind = Kind::ZOMBY;
                break;
            case 1:
                kind = Kind::HUMAN;
                break;
            }
			int factoryType;
			file >> factoryType;
			std::shared_ptr<UnitFactory> factory;
			switch (factoryType) {
			case 0:
				factory = std::shared_ptr<UnitFactory>(new BitingZombyFactory());
				break;
			case 1:
				factory = std::shared_ptr<UnitFactory>(new HumanOnBikeFactory());
				break;
			case 2:
				factory = std::shared_ptr<UnitFactory>(new HumanOnCarFactory());
				break;
			case 3:
				factory = std::shared_ptr<UnitFactory>(new HumanWithBatFactory());
				break;
			case 4:
				factory = std::shared_ptr<UnitFactory>(new HumanWithGrenadeFactory());
				break;
			case 5:
				factory = std::shared_ptr<UnitFactory>(new HumanWithGunFactory());
				break;
			case 6:
				factory = std::shared_ptr<UnitFactory>(new HumanWithSwordFactory());
				break;
			case 7:
				factory = std::shared_ptr<UnitFactory>(new KamikadzeZombyFactory());
				break;
			case 8:
				factory = std::shared_ptr<UnitFactory>(new SpitToAreaZombyFactory());
				break;
			case 9:
				factory = std::shared_ptr<UnitFactory>(new SpitToEnemyZombyFactory());
				break;
			case 10:
				factory = std::shared_ptr<UnitFactory>(new StinkyZombyFactory());
				break;
			case 11:
				factory = std::shared_ptr<UnitFactory>(new StrongZombyFactory());
				break;
			default:
				factory = nullptr;
				std::cout << "Incorrect save File\n";
			}
            int x;
            int y;
            file >> x;
            file >> y;
            return std::shared_ptr<Tower>(new Tower(level, hp, damage, size, unitCount, kind, factory, mediator, x, y));
		}
		else {
			return nullptr;
		}
	}
	else {
		std::cout << "Incorrect save file\n";
		return nullptr;
	}
}

std::shared_ptr<Unit> Loader::getUnit()
{
	std::string symb;
	file >> symb;
	if (symb == "U") {
		int isExist;
		file >> isExist;
		if (isExist == 1) {
			int type;
			file >> type;
			int hp;
			file >> hp;
			int maxHP;
			file >> maxHP;
			int ownArmor;
			file >> ownArmor;
			int ownDamage;
			file >> ownDamage;
			bool visability;
			int visInt;
			file >> visInt;
			if (visInt == 1) {
				visability = true;
			}
			else {
				visability = false;
			}
			int level;
			file >> level;
			int landDamage;
			file >> landDamage;
			int landDefence;
			file >> landDefence;
			int observerSize;
			file >> observerSize;
			int observerCount;
			file >> observerCount;
			int coordX;
			file >> coordX;
			int coordY;
			file >> coordY;
            size_t lastStep;
            file >> lastStep;

			std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers = std::shared_ptr<std::shared_ptr<ObserverInterface>[]>(new std::shared_ptr<ObserverInterface>[observerSize]);
			for (int i = 0; i < observerCount; i++) {
				int tX;
				int tY;
				file >> tX;
				file >> tY;
				observers[i] = field->getCell(tX, tY)->getTower();
			}
			
			switch (type) {
			case 0:
                return std::shared_ptr<Unit>(new BitingZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 1:
                return std::shared_ptr<Unit>(new HumanOnBike(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 2:
                return std::shared_ptr<Unit>(new HumanOnCar(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 3:
                return std::shared_ptr<Unit>(new HumanWithBat(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 4:
                return std::shared_ptr<Unit>(new HumanWithGrenade(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 5:
                return std::shared_ptr<Unit>(new HumanWithGun(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 6:
                return std::shared_ptr<Unit>(new HumanWithSword(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 7:
                return std::shared_ptr<Unit>(new KamikadzeZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 8:
                return std::shared_ptr<Unit>(new SpitToAreaZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 9:
                return std::shared_ptr<Unit>(new SpitToEnemyZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 10:
                return std::shared_ptr<Unit>(new StinkyZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			case 11:
                return std::shared_ptr<Unit>(new StrongZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep));
			default:
				std::cout << "Incorrect save File\n";
				return nullptr;
			}
		}
		else {

			return nullptr;
		}
	}
	else {
		std::cout << "Incorrect save file\n";
		return nullptr;
	}
}

std::shared_ptr<NeutralObject> Loader::getObj()
{
	std::string symb;
	file >> symb;
	if (symb == "O") {
		int isExist;
		file >> isExist;
		if (isExist == 1) {
			int type;
			file >> type;
			switch (type) {
			case 0:
				return std::shared_ptr<NeutralObject>(new LargeArmorObject());
			case 1:
				return std::shared_ptr<NeutralObject>(new LargeMedicine());
			case 2:
				return std::shared_ptr<NeutralObject>(new SmallArmorObject());
			case 3:
				return std::shared_ptr<NeutralObject>(new SmallMedicine());
			default:
				return nullptr;
			}
		}
		else {
			return nullptr;
		}
	}
	else {
		std::cout << "Incorrect file\n";
		return nullptr;
	}
}

Loader::Loader()
{
	file.open("lastSave.txt");
    mediator = std::shared_ptr<Mediator>(new Mediator());
}


Loader::~Loader()
{
	file.close();
}

std::shared_ptr<Field> Loader::loadField()
{
	int w;
	int h;
	file >> w;
	file >> h;
	field = std::shared_ptr<Field>(new Field(h, w));
	for (int i = 0; i < w; i++) {
		setLastCell(i, 0);
	}
	for (int i = 0; i < w; i++) {
		setLastCell(i, h - 1);
	}
	for (int i = 1; i < h - 1; i++) {
		for (int j = 0; j < w; j++) {
			setCell(j, i);
		}
	}

    mediator->setField(field);
	field->setMediator(mediator);
	return field;
}


void Loader::setMediator(std::shared_ptr<Mediator> mediator) {
    this->mediator = mediator;
}

GameMode Loader::loadGameMode() {
    int mode;
    file >> mode;
    if (mode == 2) {
        return GameMode::TWO_PLAYERS_GAME;
    }
    else {
        return GameMode::SOLO_GAME;
    }
}


size_t Loader::loadStepNumber() {
    size_t stepNumber;
    file >> stepNumber;
    return stepNumber;
}


std::shared_ptr<State> Loader::loadState() {
    std::shared_ptr<State> state;
    int typeI;
    int kindI;
    Kind kind;
    int resourses;
    file >> typeI >> kindI >> resourses;
    if(kindI == 0) {
        kind = Kind::ZOMBY;
    }
    else {
        kind = Kind::HUMAN;
    }
    if (typeI == 0) {
        std::shared_ptr<Facade> facade(new Facade(kind, field));
        state = std::shared_ptr<State>(new TowerSettingState(kind, 0, field, facade));
    }
    else {
        std::shared_ptr<Facade> facade(new Facade(kind, field));
        state = std::shared_ptr<State>(new UnitSettingState(kind, 0, field, facade));
    }
    state->setResources(resourses);
    return state;
}
