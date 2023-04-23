#include "TerrainBoardUnit.h"

QJsonObject TerrainBoardUnit::getSnapshot() {
	QJsonObject terrainUnitSnapshot;
	terrainUnitSnapshot.insert("type", "terrain");
	terrainUnitSnapshot.insert("subtype", getName().c_str());
	return terrainUnitSnapshot;
}