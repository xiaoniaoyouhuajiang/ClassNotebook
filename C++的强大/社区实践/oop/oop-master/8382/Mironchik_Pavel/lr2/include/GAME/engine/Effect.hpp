#pragma once

#include <cstring>
#include <set>
#include <memory>

#include <GAME/engine/Attachable.hpp>
#include <GAME/engine/BoardListener.hpp>

using std::set;
using std::shared_ptr;

class Unit;

class Effect: public Attachable<Unit>, public BoardListener {
public:
	enum EffectName {
		LAVA_EFFECT,
		SEA_EFFECT,
		GROUND_EFFECT,

		HEAL_EFFECT,
		CHANCEL_EFFECT,
		BLACK_HOLE_EFFECT
	};

private:
	EffectName _name;
	bool _isValid = true;

public:

	Effect(const Effect& other);
	Effect(EffectName name);

	EffectName name() const;

	bool valid();
	void valid(bool valid);

	bool operator==(const Effect& other);
	Effect& operator=(const Effect& other);

	virtual void onObjectMoved(GameObject& object, sf::Vector2i& from, sf::Vector2i& to) override;
	virtual void onObjectDetached(GameObject& object) override;

	virtual void onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) {}
	virtual void onOriginDetached(Unit& origin) {}

	virtual float transformHealth(float health) const { return health; }
	virtual float transformMaxHealth(float maxHealth) const { return maxHealth; }
	virtual float transformSpeed(float speed) const { return speed; }
	virtual float transformAttack(float attack) const { return attack; }
	virtual float transformAttackRange(float range) const { return range; }
};

class EffectsComparator {
public:
	bool operator()(const shared_ptr<Effect>& ef1, const shared_ptr<Effect>& ef2) const {
		return ef1->name() < ef2->name();
	}
};

class EffectsSet : public set<shared_ptr<Effect>, EffectsComparator> {
private:
	Unit* _unit;

public:
	EffectsSet(Unit& unit) {
		_unit = &unit;
	}

	void removeInvalid() {
		for (auto it = begin(); it != end();) {
			if (!(*it)->valid()) 
				it = erase(it);
			else
				it++;
		}
	}

	shared_ptr<Effect> find(Effect::EffectName name) {
		for (auto& effect : *this) {
			if (effect->name() == name)
				return effect;
		}

		throw 1;
	}
};