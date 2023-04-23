#pragma once

#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/utils/List.hpp>
#include <GAME/utils/PathSearcher.hpp>
#include <GAME/engine/GameObject.hpp>
#include <GAME/graphics/CellDrawer.hpp>
#include <GAME/engine/Effect.hpp>
#include <GAME/engine/Properties.hpp>
#include <GAME/graphics/HealthDrawer.hpp>
#include <GAME/engine/Provider.hpp>
#include <GAME/engine/behaviour/BaseUnitClickBehaviour.hpp>
#include <GAME/engine/behaviour/UnitAttackBehaviour.hpp>
#include <GAME/engine/behaviour/UnitMoveBehaviour.hpp>
#include <GAME/engine/behaviour/BaseUnitAttackBehaviour.hpp>
#include <GAME/engine/behaviour/BaseUnitMoveBehaviour.hpp>

class GameObject;

using std::shared_ptr;

class Unit : public GameObject, public Provider<Unit> {
private:
	Properties _properties;
	Properties _curProperties;
	int squad = 0;
	EffectsSet _effects = EffectsSet(*this);
	HealthDrawer _healthDrawer = HealthDrawer(*this);
	shared_ptr<CellClickBehaviour<Unit>> _clickBehaviour = shared_ptr<CellClickBehaviour<Unit>>(new BaseUnitClickBehaviour((Provider<Unit>*)this));
	shared_ptr<UnitAttackBehaviour> _attackBehaviour = shared_ptr<UnitAttackBehaviour>(new BaseUnitAttackBehaviour((Provider<Unit>*)this));
	shared_ptr<UnitMoveBehaviour> _moveBehaviour = shared_ptr<BaseUnitMoveBehaviour>(new BaseUnitMoveBehaviour((Provider<Unit>*)this));
	mutable TextureCellDrawer textureDrawer;
	mutable ColorCellDrawer attackDrawer = ColorCellDrawer(sf::Color(254, 23, 77, 50));
	mutable List<sf::Vector2i>* attackCells = nullptr;

	void transformProperties();

protected:
	Unit(istream& is, InObjectsTable& table);
	virtual void writeObject(ostream& os, OutObjectsTable& table) override;

public:
	Unit(int squad);
	Unit(const Unit& from);
	virtual ~Unit() override;

	void addEffect(Effect* effect);
	void removeEffect(Effect* effect);
	void removeEffect(Effect::EffectName effectName);

	void drawTexture(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawAchievableCells(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawAttackCells(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawHealth(sf::RenderTarget& target, sf::RenderStates states) const;
	List<sf::Vector2i>* computeAttackCells() const;

	void setHealth(float health);
	float getHealth() const;

	void setMaxHealth(float maxHealth);
	float getMaxHealth() const;

	void setAttack(float attack);
	float getAttack() const;

	void setAttackRange(float attackRange);
	float getAttackRange() const;

	void setSpeed(int speed);
	int getSpeed() const;

	int getSquad() const;

	void attackBehaviour(shared_ptr<UnitAttackBehaviour> attackBehaviour);
	shared_ptr<UnitAttackBehaviour> attackBehaviour();

	void moveBehaviour(shared_ptr<UnitMoveBehaviour> moveBehaviour);
	shared_ptr<UnitMoveBehaviour> moveBehaviour();

	void validateAttackCells() const;
	int distanceTo(const sf::Vector2i& object) const;

	virtual Unit& provide() override;

	virtual bool canGoToCell(const GameBoard& board, const sf::Vector2i& cellPosition) const;
	virtual bool canAttack(const sf::Vector2i& cellPosition) const;

	void setTexture(sf::Texture& texture);

	virtual bool onClick(sf::Vector2i& cell) override;

	// must call super
	virtual void onMapChanged() override;
	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	GameObject* copy() override;
	virtual int info() const override;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void fillLogInfo(LogInfo& info);
};