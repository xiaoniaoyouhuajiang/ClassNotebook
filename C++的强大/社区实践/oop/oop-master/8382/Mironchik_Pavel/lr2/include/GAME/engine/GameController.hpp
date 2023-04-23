#pragma once

#include <memory>

#include <SFML/Graphics/Rect.hpp>
#include <GAME/factory/Factory.hpp>

using std::shared_ptr;

class GameObject;
class GameBoard;
class Stone;
class Neutral;
class Heal;
class Chancel;
class BlackHole;

class GameController {
private:
	GameBoard* board;
	BumSoldierFactory _bumSoldierF;
	PeasantFactory _peasantF;
	CleverTowerFactory _clewerTowerF;
	MountedShooterFactory _mountedShooterF;
	MountedWarriorFactory _mountedWarriorF;
	StrongTowerFactory _strongTowerF;
	HomeFactory _homeFactory;

	int unitsCount = 0;
	int unitsMax = 100;

	bool isCellAvailable(const sf::Vector2i& cell);
	sf::Vector2i findAvailablePosition(const sf::Rect<int>& rect, Unit* unit);

	void attach(GameBoard* board);

	friend class GameBoard;
public:
	GameController();
	GameController(GameBoard* board);
	GameController(const GameController& from);

	shared_ptr<BumSoldier> createBoomSoldier(int squad);
	shared_ptr<Peasant> createPeasant(int squad);
	shared_ptr<CleverTower> createClewerTower(int squad);
	shared_ptr<StrongTower> createStrongTower(int squad);
	shared_ptr<MountedShooter> createMountedShooter(int squad);
	shared_ptr<MountedWarrior> createMountedWarrior(int squad);
	shared_ptr<Home> createHome(int squad);

	shared_ptr<Stone> createStone();
	shared_ptr<Heal> createHeal();
	shared_ptr<Chancel> createChancel();
	shared_ptr<BlackHole> createBlackHole();

	shared_ptr<Neutral> createNeutral(int info);
	shared_ptr<Unit> createUnit(int info, int squad);

	void damageUnit(Unit& unit, float damage);

	bool addNeutral(shared_ptr<Neutral> neutral, const sf::Vector2i& position);
	bool addUnit(shared_ptr<Unit> unit, const sf::Vector2i& position);
	bool removeUnit(int unitId);
};
