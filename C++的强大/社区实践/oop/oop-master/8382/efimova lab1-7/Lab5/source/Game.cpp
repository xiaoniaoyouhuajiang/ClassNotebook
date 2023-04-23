#include "Game.h"
#include "Infantry.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "UItoBackendConnector.h"
#include "PongoBaseBoardUnit.h"
#include "ActionDispatcher.h"
#include <fstream>
#include <sstream>
//работа с файлами save e load
Game* Game::mInstance = nullptr;

Game* Game::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Game();
	}
	return mInstance;
}

void Game::initGUI(int argc, char* argv[]) {
	qInfo() << "--------------------Game Start----------------------";
	qInfo() << " ";
	//Initialize GUI
	qmlRegisterSingletonType<UItoBackendConnector>("game", 1, 0, "UIConnector", UItoBackendConnector::UItoBackendConnector_singletonTypeProvider);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	_qApp = new QGuiApplication(argc, argv);
	_qApp->setOrganizationName("somename");
	_qApp->setOrganizationDomain("somename");
	_qEngine = new QQmlApplicationEngine();
	const QUrl url(QStringLiteral("qrc:/main.qml"));	//Path to main GUI file
	QObject::connect(_qEngine, &QQmlApplicationEngine::objectCreated,
		_qApp, [url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);				//If there is no such file
		}, Qt::QueuedConnection);
	QObject::connect(_qEngine, &QQmlApplicationEngine::quit, _qApp, &QGuiApplication::quit);
	_qEngine->load(url);
}

int Game::Start() {
	return _qApp->exec();
}

void Game::_debug_demo() {
	
}

void Game::initBoard(int sizeX, int sizeY, int maxAllowedUnits) {
	//_connector = UItoBackendConnector::getInstance();
	//Initializze game board and rules
	qInfo() << "initializing board";
	auto boardProp = new Board::BoardProperties;
	boardProp->sizeX = sizeX;
	boardProp->sizeY = sizeY;
	boardProp->maxAllowedUnits = maxAllowedUnits;
	BoardUnit::resetUnitCount();
	PongoBoardUnit::resetUnitCount();
	mGameBoard = new Board(boardProp);
	mActionDispatcher = new ActionDispatcher(mGameBoard);
	auto base = new PongoBaseBoardUnit();
	if (!mGameBoard->getCellAt(4, 9).isEmpty)
		mGameBoard->removeUnit(4, 9);
	mGameBoard->addUnit(base, 4, 9);
	changedCells = new std::vector<ActionDispatcher::Action>;
	//mGameBoard->_debug_print();
}

Board* Game::getBoard() {
	return mGameBoard;
}

void Game::playerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID) {
	auto unit = dynamic_cast<PlayableBoardUnit*>(fromCell.unit);
	changedCells->clear();
	if (unit != nullptr) {
		auto metaVec = unit->userAction(toCell, actionID);
		for (int i = 0; i < metaVec.size(); i++)
			mActionDispatcher->push_back(metaVec[i]);
		changedCells = mActionDispatcher->flush();
	}
	qInfo() << "Total pongo unit count:" << PongoBoardUnit::getUnitCount();
}

std::vector<ActionDispatcher::Action>* Game::getCellsToUpdate() {
	return changedCells;
}
//работа с файлами
bool Game::save(std::string fileName) {
	auto fileStream = new std::fstream(fileName, std::ios::out | std::ios::trunc);

	if (!fileStream->good()) {
		fileStream->close();
		return 0;
	}

	auto boardSnapshot = mGameBoard->getSnapshot();

	QJsonDocument gameSnapshot(boardSnapshot);//скомпинов. все юниты, рельеф
	QString stringJson(gameSnapshot.toJson(QJsonDocument::Compact));

	qInfo() << stringJson;//выписываем док. json

	std::string stringJsonStd = stringJson.toStdString();//возвр. это в кач.строки

	(*fileStream) << stringJsonStd.c_str();//преобразуем в строку и в cout

	fileStream->close();
	return 1;
}
//работа с файлами
//все также в обр. порядке
bool Game::load(std::string fileName) {
	auto fileStream = new std::fstream(fileName, std::ios::in);

	if (!fileStream->good()) {
		fileStream->close();
		return 0;
	}

	std::string JsonStrStd;
	(*fileStream) >> JsonStrStd;

	BoardUnit::resetUnitCount();
	PongoBoardUnit::resetUnitCount();

	QString stringJson = QString::fromStdString(JsonStrStd);

	QJsonDocument gameSnapshot = QJsonDocument::fromJson(stringJson.toUtf8());

	QJsonObject boardSnapshot = gameSnapshot.object();

	//delete mGameBoard;

	mGameBoard = new Board(boardSnapshot);
	mActionDispatcher = new ActionDispatcher(mGameBoard);
	changedCells = new std::vector<ActionDispatcher::Action>;

	return 1;
}


