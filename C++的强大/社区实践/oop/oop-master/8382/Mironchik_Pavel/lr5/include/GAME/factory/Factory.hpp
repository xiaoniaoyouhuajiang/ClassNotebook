#pragma once

#include <GAME/engine/GameObject.hpp>
#include <GAME/engine/units/BumSoldier.hpp>
#include <GAME/engine/units/CleverTower.hpp>
#include <GAME/engine/units/MountedShooter.hpp>
#include <GAME/engine/units/MountedWarrior.hpp>
#include <GAME/engine/units/Peasant.hpp>
#include <GAME/engine/units/StrongTower.hpp>
#include <GAME/engine/units/Home.hpp>

class Factory {
public:
	virtual GameObject* create(int squad) = 0;
};

class PeasantFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new Peasant(squad);
	}
};

class BumSoldierFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new BumSoldier(squad);
	}
};

class CleverTowerFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new CleverTower(squad);
	}
};

class StrongTowerFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new StrongTower(squad);
	}
};

class MountedShooterFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new MountedShooter(squad);
	}
};

class MountedWarriorFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new MountedWarrior(squad);
	}
};

class HomeFactory : Factory {
public:
	GameObject* create(int squad) override {
		return new Home(squad);
	}
};