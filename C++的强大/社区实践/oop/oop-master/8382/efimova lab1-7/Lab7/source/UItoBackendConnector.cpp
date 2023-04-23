#include "UItoBackendConnector.h"
#include "PlayableBoardUnit.h"
#include <QDebug>
#include "Logger.h"

UItoBackendConnector* UItoBackendConnector::mInstance = nullptr;

UItoBackendConnector::UItoBackendConnector(QObject* parent) {
	mGame = Game::getInstance();
}

QObject* UItoBackendConnector::UItoBackendConnector_singletonTypeProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)

	auto connector = new UItoBackendConnector();
	mInstance = connector;
	return connector;
}

UItoBackendConnector* UItoBackendConnector::getInstance() {
	return mInstance;
}

QJsonObject UItoBackendConnector::initBoard(int sizeX, int sizeY, int maxAllowedUnits) {
	std::vector<std::string> users;
	users.push_back("Player 1");
	users.push_back("Player 2");
	mGame->initGame(0, users, sizeX, sizeY, maxAllowedUnits);
	QJsonObject data;
	QJsonArray arr;
	for (int i = 0; i < sizeY; i++) {
		QJsonArray tarr;
		for (int j = 0; j < sizeX; j++) {
			QJsonObject cell;
			Board::BoardCell tcell = mGame->getBoard()->getCellAt(j, i);
			cell.insert("terrain_unit", tcell.terrainUnit->getName().c_str());
			if (!tcell.isEmpty) {
				cell.insert("board_unit", tcell.unit->getName().c_str());
			}
			else
				cell.insert("board_unit", "empty");
			tarr.append(cell);
		}
		arr.append(tarr);
	}
	data.insert("currentUser", mGame->getCurrentUser()->getName().c_str());
	data.insert("board", arr);
	return data;
}

QJsonObject UItoBackendConnector::getBoardUnitAtCell(int x, int y) {
	auto cell = mGame->getBoard()->getCellAt(x, y);
	QJsonObject cellObject{ {"x", x}, {"y", y} };
	QJsonObject terrainUnit;
	terrainUnit.insert("name", cell.terrainUnit->getName().c_str());
	cellObject.insert("terrain_unit", terrainUnit);
	if (!cell.isEmpty) {
		QJsonObject boardUnit;
		boardUnit.insert("name", QString(cell.unit->getName().c_str()));
		auto playable_unit = dynamic_cast<PlayableBoardUnit*>(cell.unit);
		if (playable_unit != nullptr) {
			QJsonObject stats{
				{"health", playable_unit->getStats().health},
				{"armor", playable_unit->getStats().armor},
				{"attack", playable_unit->getStats().attack}
			};
			boardUnit.insert("hasStats", 1);
			boardUnit.insert("stats", stats);
			
			
		}
		else
			boardUnit.insert("hasStats", 0);

		auto base_unit = dynamic_cast<PongoBaseBoardUnit*>(cell.unit);
		auto pongo_unit = dynamic_cast<PongoBoardUnit*>(cell.unit);
		if (base_unit != nullptr)
			boardUnit.insert("user", base_unit->getUser()->getName().c_str());
		else if (pongo_unit != nullptr)
			boardUnit.insert("user", pongo_unit->getUser()->getName().c_str());
		else
			boardUnit.insert("user", "empty");
		cellObject.insert("board_unit", boardUnit);
	}
	else {
		QJsonObject boardUnit;
		boardUnit.insert("name", "empty");
		cellObject.insert("board_unit", boardUnit);
	}
	return cellObject;
}

QJsonObject UItoBackendConnector::getUpdatedCells() {
	auto arr = mGame->getCellsToUpdate();
	QJsonArray actions;
	QJsonObject data;
	for (int i = 0; i < arr->size(); i++) {
		auto action = (*arr)[i];
		auto fromCellObject = getBoardUnitAtCell(action.fromCell.first, action.fromCell.second);
		QJsonObject actionObject;
		actionObject.insert("fromCell", fromCellObject);
		if (action.actionType != "empty") {
			auto toCellObject = getBoardUnitAtCell(action.toCell.first, action.toCell.second);
			actionObject.insert("toCell", toCellObject);
			actionObject.insert("actionType", action.actionType.c_str());
		}
		else {
			actionObject.insert("actionType", "empty");
		}
		actions.append(actionObject);
	}
	data.insert("newCurrentUser", mGame->getCurrentUser()->getName().c_str());
	data.insert("updatedCells", actions);
	return data;
}

void UItoBackendConnector::action(QJsonObject action) {
	QJsonObject invokingCellObj = action.value("invoking_cell").toObject();
	auto targetCellObj = action.value("target_cell").toObject();
	auto invokingCell = mGame->
		getBoard()->
		getCellAt(invokingCellObj.value("x").toInt(), invokingCellObj.value("y").toInt());
	auto targetCell = mGame->
		getBoard()->
		getCellAt(targetCellObj.value("x").toInt(), targetCellObj.value("y").toInt());
	int actionID = action.value("action_id").toInt();
	mGame->playerAction(invokingCell, targetCell, actionID);
	emit boardChanged();

}

QJsonObject UItoBackendConnector::checkUnitAction(QJsonObject action) {
	QJsonObject invokingCellObj = action.value("invoking_cell").toObject();
	auto targetCellObj = action.value("target_cell").toObject();
	auto invokingCell = mGame->
		getBoard()->
		getCellAt(invokingCellObj.value("x").toInt(), invokingCellObj.value("y").toInt());
	auto targetCell = mGame->
		getBoard()->
		getCellAt(targetCellObj.value("x").toInt(), targetCellObj.value("y").toInt());
	int actionID = action.value("action_id").toInt();
	auto meta = mGame->checkPlayerAction(invokingCell, targetCell, actionID);
	QJsonObject actionType;
	if (meta.isMove)
		actionType.insert("actionType", "move");
	else if (meta.isAttack)
		actionType.insert("actionType", "attack");
	else if (meta.isHeal)
		actionType.insert("actionType", "heal");
	else if (meta.isCreate)
		actionType.insert("actionType", "create");
	else
		actionType.insert("actionType", "empty");
	return actionType;
}

void UItoBackendConnector::save(QString fileUrl) {
	std::string url = fileUrl.toStdString();
	url = url.erase(0, 8);
	mGame->save(url);
}

QJsonObject UItoBackendConnector::load(QString fileUrl) {
	std::string url = fileUrl.toStdString();
	url = url.erase(0, 8);
	mGame->load(url);
	auto boardProperties = mGame->getBoard()->getBoardProperties();
	QJsonObject boardProp;
	boardProp.insert("sizeX", boardProperties.sizeX);
	boardProp.insert("sizeY", boardProperties.sizeY);
	return boardProp;
}

void UItoBackendConnector::shutdown() {
	delete mGame;
}
