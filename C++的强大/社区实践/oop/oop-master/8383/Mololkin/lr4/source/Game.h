#pragma once
#include <iostream>
#include <utility>
#include <fstream>
#include <ctime>
#include "GameBoard.h"
#include "IUnit.h"
#include "Mediator.h"
#include "Logger.h"

class Game
{
private:
	GameBoard* board;
	LoggerProxy* logger;

public:
	Game();
	void startGame();
};


class Command
{
public:
	virtual bool execute() = 0;
};

class UnitAttackCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;
public:
	UnitAttackCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};

class ChangeLoggerCommand : public Command
{
private:
	LoggerProxy* logger;
public:
	ChangeLoggerCommand(LoggerProxy* logger) : logger(logger) {};
	bool execute() override;
};


class RestartCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;

public:
	RestartCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};

class PrintBoardCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;
public:
	PrintBoardCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};

class MoveUnitCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;

public:
	MoveUnitCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};

class AboutBaseCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;

public:
	AboutBaseCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};

class CreateUnitFromBaseCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;

public:
	CreateUnitFromBaseCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};

class AboutUnitCommand : public Command
{
private:
	GameBoard** board;
	LoggerProxy* logger;

public:
	AboutUnitCommand(GameBoard** board, LoggerProxy* logger);
	bool execute() override;
};


