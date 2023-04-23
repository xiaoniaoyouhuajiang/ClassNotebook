#include <GAME/engine/GameController.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Info.hpp>
#include <GAME/engine/Neutral.hpp>
#include <GAME/engine/units/Stone.hpp>
#include <GAME/engine/units/Heal.hpp>
#include <GAME/engine/units/Chancel.hpp>
#include <GAME/engine/units/BlackHole.hpp>

void GameController::readObject(istream& is, InObjectsTable& table) {
	ObjectInfo info;

	info = table.readInfo(is);
	assert(!info.needWrite);
	table.getObject(info, [this](void* obj) {
		this->board = (GameBoard*)obj;
	});
	Serializer::readInt(is, &unitsCount);
	Serializer::readInt(is, &unitsMax);
}

void GameController::writeObject(ostream& os, OutObjectsTable& table) {
	ObjectInfo info;

	info = table.writeInfo(os, board);
	assert(!info.needWrite);
	Serializer::writeInt(os, &unitsCount);
	Serializer::writeInt(os, &unitsMax);
}

GameController::GameController() {}

GameController::GameController(GameBoard* board): board(board) {}

GameController::GameController(const GameController& from) {
	board = from.board;
	unitsCount = from.unitsCount;
	unitsMax = from.unitsMax;
}

GameController& GameController::operator=(const GameController& other) {
	if (this == &other)
		return *this;

	board = other.board;
	unitsCount = other.unitsCount;
	unitsMax = other.unitsMax;
	return *this;
}

void GameController::attach(GameBoard* board) {
	this->board = board;
}

sf::Vector2i GameController::findAvailablePosition(const sf::Rect<int>& rect, Unit* unit) {
	if (board == nullptr)
		return sf::Vector2i(-1, -1);

	for (int x = rect.left; x < rect.left + rect.width; x++)
		for (int y = rect.top; y < rect.top + rect.height; y++) {
			sf::Vector2i cell(x, y);
			if (isCellAvailable(cell))
				return cell;
		}

	return sf::Vector2i(-1, -1);
}

bool GameController::addUnit(shared_ptr<Unit> unit, const sf::Vector2i& position) {
	if (!isCellAvailable(position))
		return false;

	if (unitsCount >= unitsMax)
		return false;

	unit->setOccupiedCell(position);
	board->attach(unit);

	LogInfo info;
	info.name = "GameController:addUnit";
	info.pushParam("unit", unit->toStringShort());
	info.pushParam("x", std::to_string(position.x));
	info.pushParam("y", std::to_string(position.y));
	Log::log(info);

	return true;
}

bool GameController::addNeutral(shared_ptr<Neutral> neutral, const sf::Vector2i& position) {
	if (!isCellAvailable(position))
		return false;

	neutral->setOccupiedCell(position);
	board->attach(neutral);

	LogInfo info;
	info.name = "GameController:addNeutral";
	info.pushParam("unit", neutral->toStringShort());
	info.pushParam("x", std::to_string(position.x));
	info.pushParam("y", std::to_string(position.y));
	Log::log(info);

	return true;
}

bool GameController::isCellAvailable(const sf::Vector2i& cell) {
	if (!board->hasCell(cell))
		return false;

	for (auto object : board->getCell(cell).objects())
		if (object->isTangible())
			return false;

	return true;
}

shared_ptr<BumSoldier> GameController::createBoomSoldier(int squad) {
	BumSoldier* unit = (BumSoldier*) _bumSoldierF.create(squad);
	return shared_ptr<BumSoldier>(unit);
}

shared_ptr<Peasant> GameController::createPeasant(int squad) {
	Peasant* unit = (Peasant*) _peasantF.create(squad);
	return shared_ptr<Peasant>(unit);
}

shared_ptr<CleverTower> GameController::createClewerTower(int squad) {
	CleverTower* unit = (CleverTower*) _clewerTowerF.create(squad);
	return shared_ptr<CleverTower>(unit);
}

shared_ptr<StrongTower> GameController::createStrongTower(int squad) {
	StrongTower* unit = (StrongTower*) _strongTowerF.create(squad);
	return shared_ptr<StrongTower>(unit);
}

shared_ptr<MountedShooter> GameController::createMountedShooter(int squad) {
	MountedShooter* unit = (MountedShooter*) _mountedShooterF.create(squad);
	return shared_ptr<MountedShooter>(unit);
}

shared_ptr<MountedWarrior> GameController::createMountedWarrior(int squad) {
	MountedWarrior* unit = (MountedWarrior*) _mountedWarriorF.create(squad);
	return shared_ptr<MountedWarrior>(unit);
}

shared_ptr<Stone> GameController::createStone() {
	Stone *stone = new Stone();
	return shared_ptr<Stone>(stone);
}

shared_ptr<Heal> GameController::createHeal() {
	Heal* heal = new Heal();
	return shared_ptr<Heal>(heal);
}

shared_ptr<Chancel> GameController::createChancel() {
	Chancel* chancel = new Chancel();
	return shared_ptr<Chancel>(chancel);
}

shared_ptr<BlackHole> GameController::createBlackHole() {
	BlackHole *hole = new BlackHole();
	return shared_ptr<BlackHole>(hole);
}

shared_ptr<Home> GameController::createHome(int squad) {
	return shared_ptr<Home>(new Home(squad));
}

bool GameController::removeUnit(int unitId) {
	if (board->detach(unitId)) {
		unitsCount--;
		return true;
	}

	return false;
}

void GameController::damageUnit(Unit& unit, float damage) {
	float health = unit.getHealth() - damage;

	unit.setHealth(health);

	if (health <= 0)
		removeUnit(unit.id());

	LogInfo info;
	info.name = "GameController:damageUnit";
	info.pushParam("target", unit.toStringFull());
	info.pushParam("damage", std::to_string(damage));
	Log::log(info);
}

shared_ptr<Unit> GameController::createUnit(int id, int squad) {
	if (id == Info::BUM_SOLDIER)
		return createBoomSoldier(squad);

	if (id == Info::CLEVER_TOWER)
		return createClewerTower(squad);

	if (id == Info::MOUNTED_WARRIOR)
		return createMountedWarrior(squad);

	if (id == Info::MOUNTED_SHOOTER)
		return createMountedShooter(squad);

	if (id == Info::PEASANT)
		return createPeasant(squad);

	if (id == Info::STRONG_TOWER)
		return createStrongTower(squad);

	if (id == Info::HOME)
		return createHome(squad);

	throw 1;
}

shared_ptr<Neutral> GameController::createNeutral(int info) {
	if (info == Info::STONE)
		return createStone();

	if (info == Info::HEAL)
		return createHeal();

	if (info == Info::CHANCEL)
		return createChancel();

	if (info == Info::BLACK_HOLE)
		return createBlackHole();

	throw 1;
}

void GameController::fillLogInfo(LogInfo& info) {
	info.name = "GameController";
	info.pushParam("unitsCount", std::to_string(unitsCount));
}

/*void GameController::synchronize() {
	unitsCount = 0;

	for (GameObject* object : board->getChildren()) {
		Unit* unit = dynamic_cast<Unit*>(object);
		if (unit != nullptr)
			unitsCount++;
	}
}*/