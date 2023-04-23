#pragma once
#include "FieldBlock.h"
#include "GameUtilities.h"
#include <string>
#include <fstream>
#include <iostream>

class GameUnits;

class FieldProperties {
public:
	Vector2D dimensions;
	FieldBlock ***blocks;

	~FieldProperties() {
		for (int i = 0; i < dimensions.x; i++) {
			delete[] blocks[i];
		}

		delete blocks;
	}

	FieldProperties() {}

	FieldProperties(Vector2D dims) : dimensions(dims) {
		blocks = new FieldBlock**[dimensions.x];
		for (int i = 0; i < dimensions.x; i++) {
			blocks[i] = new FieldBlock*[dimensions.y];
		}
	}

	FieldProperties(const FieldProperties &props) : dimensions(props.dimensions){
		blocks = new FieldBlock**[dimensions.x];
		for (int i = 0; i < dimensions.x; i++) {
			blocks[i] = new FieldBlock*[dimensions.y];
		}
		for (int i = 0; i < dimensions.x; i++) {
			for (int j = 0; j < dimensions.y; j++) {
				blocks[i][j]->blockType = props.blocks[i][j]->blockType;
			}
		}
	}

	FieldProperties &operator=(const FieldProperties &props) {
		if (&props == this) {
			return *this;
		}

		for (int i = 0; i < dimensions.x; i++) {
			delete[] blocks[i];
		}
		delete[] blocks;

		dimensions = props.dimensions;
		blocks = new FieldBlock**[dimensions.x];
		for (int i = 0; i < dimensions.x; i++) {
			blocks[i] = new FieldBlock*[dimensions.y];
		}

		for (int i = 0; i < dimensions.x; i++) {
			for (int j = 0; j < dimensions.y; j++) {
				blocks[i][j] = new FieldBlock(props.blocks[i][j]->blockType);
			}
		}

		return *this;

	}
};

class GameField : IBlocks{
public:
	FieldProperties fieldProps;

	Vector2D getFieldBorders();
	FieldBlock *getBlockAtLocation(Vector2D loc);
	void resizeMap(Vector2D newDimensions);


	class GameFieldSnapshot {
	private:
		FieldProperties fieldProps;
	public:
		GameFieldSnapshot(GameField *field) {
			fieldProps = field->fieldProps;
		}

		GameFieldSnapshot() = default;

		FieldProperties *getFieldInfo() {
			return &fieldProps;
		}

		friend std::ofstream &operator<<(std::ofstream &os, GameFieldSnapshot &snapshot);
		friend std::ifstream &operator>>(std::ifstream &is, GameFieldSnapshot &snapshot);
	};


	void onMove(GameUnits &units);
	void onAttack();
	void onConversion();

	GameField() = default;
	GameField(Vector2D dimensions, BlockTypes type);
	GameField(const GameField *field);
	GameField(std::string mapName);
	~GameField();

	GameField &operator=(const GameField &gameField);
	void loadField(GameFieldSnapshot *fieldSnapshot);
	GameFieldSnapshot *saveField() {
		return new GameField::GameFieldSnapshot(this);
	}
	void createBlock(Vector2D location, int type);
};

