#pragma once

#include <GAME/engine/Effect.hpp>

class Properties {
private:
	float _health = 0, _maxHealth = 0;
	float _attack = 0, _attackRange = 0;
	float _speed = 2;

public:
	Properties() {}

	Properties(Properties& from) {
		*this = from;
	}

	Properties& operator=(const Properties& from) {
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
};