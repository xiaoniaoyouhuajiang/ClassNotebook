#pragma once
#include "FieldCell.h"
#include <memory>
#include <iostream>
#include "Tower.h"
#include <QObject>
#include "NeutralObjectFactory.h"


class FieldIterator;


class Field : public QObject, public std::enable_shared_from_this<Field>
{
    Q_OBJECT
	friend class FieldIterator;
    friend class MyGraphicsView;
private:
	int height;
	int width;
	int unitCount;
	std::shared_ptr<std::shared_ptr<std::shared_ptr<FieldCell>[]>[]> fieldArr;
	std::shared_ptr<std::shared_ptr<Unit>[]> unitArr;
	std::shared_ptr<Mediator> mediator;
    std::shared_ptr<NeutralObjectFactory> objFactory;
public:
	Field(int height, int width);
	Field(const Field& other);
	Field(Field&& other);
	Field& operator=(const Field& other);
	Field& operator=(Field&& other);
	~Field();
	std::shared_ptr<Tower> createTower(int x, int y, std::shared_ptr<UnitFactory> factory);
	void printField();
	void reload();
	std::shared_ptr<FieldIterator> createIterator();
	void addUnit(std::shared_ptr<Unit> unit);
	std::shared_ptr<FieldCell> getCell(int x, int y);
	int getHeight();
	int getWidth();
	void setMediator(std::shared_ptr<Mediator> mediator);
	std::shared_ptr<Mediator> getMediator();
	std::shared_ptr<FieldIterator> begin();
	std::shared_ptr<FieldIterator> end();
    bool isGameEnd(Kind kind);
    void createObj();
signals:
    void updateSignal();
    void gameEndSignal();
};

 
class FieldIterator
{
private:
	std::shared_ptr<Field> field;
	int yCoord;
	int xCoord;
public:
	FieldIterator(std::shared_ptr<Field> field);
	~FieldIterator();
	void first();
	void end();
	void prev();
	void next();
	bool isDone();
	bool isBegin();
	std::shared_ptr<FieldCell> current();
};


