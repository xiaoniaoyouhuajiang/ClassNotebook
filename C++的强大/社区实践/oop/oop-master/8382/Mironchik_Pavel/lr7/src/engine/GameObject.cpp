#include <iostream>
#include <string>

#include <GAME/engine/GameObject.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <GAME/log/Log.hpp>
#include <GAME/serialize/Serializer.hpp>
#include <GAME/engine/units/Stone.hpp>
#include <GAME/engine/units/BlackHole.hpp>
#include <GAME/engine/units/Chancel.hpp>
#include <GAME/engine/units/Heal.hpp>

int GameObject::CUR_ID = 0;

GameObject* GameObject::readObject(istream& is, InObjectsTable& table) {
	int type;

	Serializer::readInt(is, &type);

	LogInfo logInfo;
	logInfo.name = "GameObject:readObject";
	logInfo.pushParam("type", std::to_string(type));
	Log::log(logInfo);

	if (type == Info::BLACK_HOLE)
		return new BlackHole(is, table);

	if (type == Info::BUM_SOLDIER)
		return new BumSoldier(is, table);

	if (type == Info::CHANCEL)
		return new Chancel(is, table);

	if (type == Info::CLEVER_TOWER)
		return new CleverTower(is, table);

	if (type == Info::HEAL)
		return new Heal(is, table);

	if (type == Info::HOME)
		return new Home(is, table);

	if (type == Info::MOUNTED_SHOOTER)
		return new MountedShooter(is, table);

	if (type == Info::MOUNTED_WARRIOR)
		return new MountedWarrior(is, table);

	if (type == Info::PEASANT)
		return new Peasant(is, table);

	if (type == Info::STONE)
		return new Stone(is, table);

	if (type == Info::STRONG_TOWER)
		return new StrongTower(is, table);

	LogInfo info;
	info.name = "GameObject";
	info.pushParam("info", std::to_string(type));
	info.pushParam("description", "Failed to read object from file: info is unknown");
	Log::exception(info);
}

void GameObject::writeObject(ostream& os, OutObjectsTable& table, GameObject* object) {
	int type = object->info();
	Serializer::writeInt(os, &type);
	object->writeObject(os, table);
}

GameObject::GameObject(istream& is, InObjectsTable& table) {
	ObjectInfo info;

	readTangible(is, table);
	readFocusable(is, table);

	Serializer::readInt(is, &CUR_ID);
	Serializer::readInt(is, &_id);

	info = table.readInfo(is);
	assert(!info.needWrite);
	table.getObject(info, [this](void* object) {
		this->board = (GameBoard*)object;
	});

	assert(Serializer::checkControlPoint(is));
	Serializer::read(is, &occupiedCell, sizeof(sf::Vector2i));
	Serializer::readInt(is, &attachState);
	readBoardListener(is, table);
}

void GameObject::writeObject(ostream& os, OutObjectsTable& table) {
	ObjectInfo info;

	writeTangible(os, table);
	writeFocusable(os, table);

	Serializer::writeInt(os, &CUR_ID);
	Serializer::writeInt(os, &_id);

	info = table.writeInfo(os, board);
	assert(!info.needWrite);

	Serializer::writeControlPoint(os);
	Serializer::write(os, &occupiedCell, sizeof(sf::Vector2i));
	Serializer::writeInt(os, &attachState);
	writeBoardListener(os, table);
}

GameObject::GameObject() {

}

GameObject::GameObject(const GameObject& from) {
	setTangible(from.isTangible());
	setFocusable(from.isFocusable());
	setFocused(from.isFocused());
	occupiedCell = from.occupiedCell;
}

GameObject::~GameObject() {
}

int GameObject::id() const {
	return _id;
}

void GameObject::attach(GameBoard *board) {
	this->board = board;
	onAttach();
}

void GameObject::detach() {
	onDetach();
	this->board = nullptr;
}

bool GameObject::onClick(sf::Vector2i& cell) {
	return false;
}


bool GameObject::onKeyPressed(sf::Event key) {
	return false;
}

bool GameObject::isAttached() const {
	return board != nullptr;
}

sf::Vector2i& GameObject::getOccupiedCell() const {
	return occupiedCell;
}

void GameObject::setOccupiedCell(sf::Vector2i cell) {
	sf::Vector2i prevCell = this->occupiedCell;
	this->occupiedCell = cell;

	if (board != nullptr)
		board->moveObject(id(), prevCell, occupiedCell);
}

GameBoard* GameObject::getBoard() const {
	return board;
}

void GameObject::fillLogInfo(LogInfo& info) {
	info.name = "GameObject";
	info.params.push_back(pair<string, string>("isAttached", isAttached() ? "1" : "0"));
}