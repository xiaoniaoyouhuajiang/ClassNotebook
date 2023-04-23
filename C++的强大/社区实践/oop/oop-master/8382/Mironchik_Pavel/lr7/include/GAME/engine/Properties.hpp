#pragma once

#include <string>
#include <istream>

#include <GAME/log/Log.hpp>
#include <GAME/engine/Effect.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>
#include <GAME/serialize/Serializer.hpp>

using std::istream;
using std::ostream;

class Properties : public Loggable {
private:
	float _health = 0, _maxHealth = 0;
	float _attack = 0, _attackRange = 0;
	float _speed = 2;

public:
	Properties(istream& is, InObjectsTable& table) {
		Serializer::readFloat(is, &_health);
		Serializer::readFloat(is, &_maxHealth);
		Serializer::readFloat(is, &_attack);
		Serializer::readFloat(is, &_attackRange);
		Serializer::readFloat(is, &_speed);
	}

	void writeObject(ostream& os, OutObjectsTable& table) {
		Serializer::writeFloat(os, &_health);
		Serializer::writeFloat(os, &_maxHealth);
		Serializer::writeFloat(os, &_attack);
		Serializer::writeFloat(os, &_attackRange);
		Serializer::writeFloat(os, &_speed);
	}

	Properties() {}

	Properties(Properties& from) {
		*this = from;
	}

	Properties& operator=(const Properties& from) {
		if (this == &from)
			return *this;

		_health = from._health;
		_maxHealth = from._maxHealth;
		_attack = from._attack;
		_attackRange = from._attackRange;
		_speed = from._speed;
		return *this;
	}

	float health() const { return _health; }
	void health(float health) { _health = health; }

	float maxHealth() const { return _maxHealth; }
	void maxHealth(float maxHealth) { _maxHealth = maxHealth; }

	float attack() const { return _attack; }
	void attack(float attack) { _attack = attack; }

	float attackRange() const { return _attackRange; }
	void attackRange(float attackRange) { _attackRange = attackRange; }

	float speed() const { return _speed; }
	void speed(float speed) { _speed = speed; }

	void transform(const Effect& transformer) {
		health(transformer.transformHealth(health()));
		maxHealth(transformer.transformMaxHealth(maxHealth()));
		attack(transformer.transformAttack(attack()));
		attackRange(transformer.transformAttackRange(attackRange()));
		speed(transformer.transformSpeed(speed()));
	}

	virtual void fillLogInfo(LogInfo& info) override {
		info.name = "Properties";
		info.pushParam("health", std::to_string(health()));
		info.pushParam("maxHealth", std::to_string(maxHealth()));
		info.pushParam("attack", std::to_string(attack()));
		info.pushParam("attackRange", std::to_string(attackRange()));
		info.pushParam("speed", std::to_string(speed()));
	}
};