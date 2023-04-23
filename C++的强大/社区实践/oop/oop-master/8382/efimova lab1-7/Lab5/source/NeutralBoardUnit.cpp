#include "NeutralBoardUnit.h"

QJsonObject NeutralBoardUnit::getSnapshot() {
	QJsonObject neutralObjectSnapshot;
	neutralObjectSnapshot.insert("type", "neutral");
	neutralObjectSnapshot.insert("subtype", getName().c_str());
	return neutralObjectSnapshot;
}