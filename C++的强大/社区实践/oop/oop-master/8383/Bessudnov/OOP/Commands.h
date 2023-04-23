#pragma once
#include "GameUtilities.h"

class GameUnits;
class GameBasesContainer;
class PlayerInput;

class Command {
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

class BaseCommands : public Command {
protected:
	GameBasesContainer *baseContainer;
public:
	BaseCommands(GameBasesContainer *bases) : baseContainer(bases) {}
	~BaseCommands();

	virtual void execute() = 0;
};

class UnitCommands : public Command {
protected:
	GameUnits *unitsContainer;
public:
	UnitCommands() = default;
	UnitCommands(GameUnits *units) : unitsContainer(units) {}
	~UnitCommands();

	virtual void execute() = 0;
};

class ActionUnitCommand : public UnitCommands {
private:
	Vector2D direction;
public:
	ActionUnitCommand(GameUnits *units, Vector2D dir) : UnitCommands(units), direction(dir) {}
	~ActionUnitCommand();

	void execute();
};

class UnitAttackDirectionCommand : public UnitCommands {
private:
	PlayerInput *input;
	Vector2D *dir;
public:
	UnitAttackDirectionCommand(PlayerInput *input, Vector2D *dir) : input(input), dir(dir) {
	
	}

	void execute();
};

class MoveUnitCommand : public UnitCommands {
private:
	Vector2D direction;
public:
	MoveUnitCommand(GameUnits *units, Vector2D dir) : UnitCommands(units), direction(dir) {}
	~MoveUnitCommand();

	void execute();
};

class UnitSacraficeCommand : public UnitCommands {
public:
	UnitSacraficeCommand(GameUnits *units) : UnitCommands(units) {};

	void execute();
}; 

class NextUnitCommand : public UnitCommands {
private:
	bool isNext;
public:
	NextUnitCommand(GameUnits *units, bool isNext) : UnitCommands(units), isNext(isNext) {}
	~NextUnitCommand();

	void execute();
};

class NextBaseCommand : public BaseCommands {
private:
	bool isNext;
public:
	NextBaseCommand(GameBasesContainer *bases, bool isNext) : BaseCommands(bases), isNext(isNext) {}
	~NextBaseCommand();

	void execute();
};

class SpawnUnitCommand : public BaseCommands {
private:
	char type;
public:
	SpawnUnitCommand(GameBasesContainer *bases, char type) : BaseCommands(bases), type(type) {}
	~SpawnUnitCommand();

	void execute();
};