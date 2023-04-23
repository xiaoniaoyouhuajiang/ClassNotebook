#include "pch.h"
#include "GameField.h"
#include "GameUnits.h"
#include "MyException.h"
#include "Logger.h"

Vector2D GameField::getFieldBorders() {
	return Vector2D(fieldProps.dimensions.x - 1, fieldProps.dimensions.y - 1);
}

FieldBlock *GameField::getBlockAtLocation(Vector2D loc) {
	return fieldProps.blocks[loc.x][loc.y];
}

void GameField::resizeMap(Vector2D newDimensions) {
	fieldProps.dimensions = newDimensions;
	fieldProps.blocks = new FieldBlock**[fieldProps.dimensions.x];
	for (int i = 0; i < fieldProps.dimensions.x; i++) {
		fieldProps.blocks[i] = new FieldBlock*[fieldProps.dimensions.y];
	}

	for (int i = 0; i < fieldProps.dimensions.x; i++) {
		for (int j = 0; j < fieldProps.dimensions.y; j++) {
			createBlock(Vector2D(i, j), BlockTypes::Grass);
		}
	}
}

void GameField::onMove(GameUnits &units) {
	Vector2D loc = units.units[units.currentUnitIndex]->unitProps.location;
	fieldProps.blocks[loc.x][loc.y]->onMove(units);
}

void GameField::onAttack() {
}

void GameField::onConversion() {
}

GameField::GameField(std::string mapName) {
	try {
		std::ifstream ifs;
		ifs.open(mapName, std::ifstream::in);
		if (!ifs.is_open()) {
			throw FileException("Failed to Load file", mapName, ifs.rdstate());
		}
		int blockIndex;

		ifs >> fieldProps.dimensions.x >> fieldProps.dimensions.y;

		GameUtilities::clamp(fieldProps.dimensions, FIELD_MAX_SIZE, FIELD_MIN_SIZE);
		fieldProps.dimensions.x += 2;
		fieldProps.dimensions.y += 2;

		fieldProps.blocks = new FieldBlock**[fieldProps.dimensions.x];
		for (int i = 0; i < fieldProps.dimensions.x; i++) {
			fieldProps.blocks[i] = new FieldBlock*[fieldProps.dimensions.y];
		}

		for (int i = 0; i < fieldProps.dimensions.x; i++) {
			for (int j = 0; j < fieldProps.dimensions.y; j++) {
				if (i != 0 && j != 0 && i != fieldProps.dimensions.x - 1 && j != fieldProps.dimensions.y - 1) {
					ifs >> blockIndex;
					createBlock(Vector2D(i, j), blockIndex);
				} else {
					createBlock(Vector2D(i, j), 4);
				}
			}
		}

		ifs.close();
	} catch (FileException &exception) {
		LoggerProxy logger;
		logger.logEvent(new LogEntry(exception.getMes()));
	}
}

GameField::GameField(Vector2D dimensions, BlockTypes type) : fieldProps(dimensions) {
	for (int i = 0; i < fieldProps.dimensions.x; i++) {
		for (int j = 0; j < fieldProps.dimensions.y; j++) {
			fieldProps.blocks[i][j]->blockType = type;
		}
	}
}

GameField::GameField(const GameField *field) : fieldProps(field->fieldProps){
	for (int i = 0; i < fieldProps.dimensions.x; i++) {
		for (int j = 0; j < fieldProps.dimensions.y; j++) {
			fieldProps.blocks[i][j]->blockType = field->fieldProps.blocks[i][j]->blockType;
		}
	}
}


GameField::~GameField() {

}

GameField &GameField::operator=(const GameField &gameField) {
	if (&gameField == this) {
		return *this;
	}

	this->fieldProps = gameField.fieldProps;


	return *this;
}

void GameField::loadField(GameFieldSnapshot *fieldSnapshot) {
	fieldProps = *fieldSnapshot->getFieldInfo();
}

void GameField::createBlock(Vector2D location, int type) {
	switch (type) {
	case 0:
		fieldProps.blocks[location.x][location.y] = new GrassBlock;
		break;
	case 1:
		fieldProps.blocks[location.x][location.y] = new BoulderBlock;
		break;
	case 2:
		fieldProps.blocks[location.x][location.y] = new WaterBlock;
		break;
	case 3:
		fieldProps.blocks[location.x][location.y] = new BushBlock;
		break;
	case 4:
		fieldProps.blocks[location.x][location.y] = new BaseBlock;
		break;
	default:
		fieldProps.blocks[location.x][location.y] = new GrassBlock;

	}
}

std::ofstream & operator<<(std::ofstream & os, GameField::GameFieldSnapshot & snapshot) {
	os << snapshot.fieldProps.dimensions << std::endl;;
	for (int i = 0; i < snapshot.fieldProps.dimensions.x; i++) {
		for (int j = 0; j < snapshot.fieldProps.dimensions.y; j++) {
			os << snapshot.fieldProps.blocks[i][j]->blockType << " ";
		}

		os << std::endl;
	}
	return os;
}

std::ifstream & operator>>(std::ifstream & is, GameField::GameFieldSnapshot & snapshot) {
	for (int i = 0; i < snapshot.fieldProps.dimensions.x; i++) {
		delete[] snapshot.fieldProps.blocks[i];
	}

	delete snapshot.fieldProps.blocks;
	is >> snapshot.fieldProps.dimensions;

	snapshot.fieldProps.blocks = new FieldBlock**[snapshot.fieldProps.dimensions.x];
	for (int i = 0; i < snapshot.fieldProps.dimensions.x; i++) {
		snapshot.fieldProps.blocks[i] = new FieldBlock*[snapshot.fieldProps.dimensions.y];
	}
	for (int i = 0; i < snapshot.fieldProps.dimensions.x; i++) {
		for (int j = 0; j < snapshot.fieldProps.dimensions.y; j++) {
			snapshot.fieldProps.blocks[i][j] = new FieldBlock;
			int blockType;
			is >> blockType;
			snapshot.fieldProps.blocks[i][j]->blockType = static_cast<BlockTypes>(blockType);
		}
	}

	return is;
}
