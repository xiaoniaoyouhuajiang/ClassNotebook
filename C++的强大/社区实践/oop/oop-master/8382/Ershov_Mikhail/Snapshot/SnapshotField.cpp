#include "SnapshotField.h"

SnapshotField::SnapshotField(int size, Cell** c, int turn) {
	this->size = size;
	this->whoseTurn = turn;
	cell = new Cell * [size];
	for (int i = 0; i < size; i++) {
		cell[i] = new Cell[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cell[i][j].setLandscape(c[i][j].getLandscape());
			cell[i][j].setNeutral(c[i][j].getNeutral());
			cell[i][j].setBase(c[i][j].getBase());
			cell[i][j].setUnit(c[i][j].getUnit());
		}
	}
}

SnapshotField::SnapshotField() {
	size = -1;
	cell = NULL;
}

int SnapshotField::getSize() const {
	return size;
}

Cell** SnapshotField::getCell() const {
	if (cell != NULL) return cell;
}

int SnapshotField::getWhoseTurn() const {
	return whoseTurn;
}
