#include "pch.h"
#include "Originator.h"
#include "Units.h"
#include "Object.h"
#include "Game.hpp"
#include "Rules.h"




Originator::Originator(std::string fout, bool isSave) :fout(fout) {
	if (isSave) {
		out.open(fout, std::ios_base::out | std::ios_base::trunc);
	}
	else {
		fin.open(fout);
	}
}

void Originator::takeMemento(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Units* selectedUnit, int& currNumBase) {
	out << game->_multiplayer << " " << game->_countermoves_1 << " " << game->_countermoves_2 << std::endl;
	out << game->xMax() << " " << game->yMax() << std::endl; 
	for (int i = 0; i <= game->field->getHeight()-1; i++)
	{
		for (int j = 0; j < game->field->getWidth(); j++)
		{
			if (game->field->getObject(i, j)->object != ' ')
			out << game->field->getObject(i, j)->object << " " << game->field->getObject(i, j)->color << " ";
		}
		out << std::endl;
	}
	out << "Cave" << std::endl;
	out << game->neutral->cave->object<< " " << game->neutral->cave->getX() << " " << game->neutral->cave->getY() << std::endl;
	out << "Tablet" << std::endl;
	out << game->neutral->tablet->object << " " << game->neutral->tablet->getX() << " " << game->neutral->tablet->getY() << std::endl;
	out << "Ruin" << std::endl;
	out << game->neutral->ruin->object << " " << game->neutral->ruin->getX() << " " << game->neutral->ruin->getY() << std::endl;
	out << "Pab" << std::endl;
	out << game->neutral->pab->object << " " << game->neutral->pab->getX() << " " << game->neutral->pab->getY() << std::endl;
	out << "Base_1" << std::endl;
	out << game->base->X << " " << game->base->Y << " " << game->base->color << " " << game->base->getEster() 
		<< " " << game->base->getHealth() << " " << game->base->count_units << std::endl;
	for (int j = 0; j < 3; j++) out << game->base->list.count_unit[j]    << " "; out << std::endl;
	for (int j = 0; j < 3; j++) out << game->base->list.count_warlock[j] << " "; out << std::endl;
	for (int j = 0; j < 3; j++) out << game->base->list.count_archer[j]  << " "; out << std::endl;
	for (int j = 0; j < 3; j++) out << game->base->list.count_warrior[j] << " "; out << std::endl;
	out << "Units" << std::endl;
	int point;
	if(game->base->count_units == 0)
		out << "Empty" << std::endl;
	else
		for (int i = 0; i < game->base->count_units; i++)
		{
			Units* un;
			un = game->base->getLink(i+1);
			out << un->message << std::endl;
			out << un->name.returnName()	 << " " << un->color				 << " " << un->health.returnHealth() << " " << un->armor.returnArmor()  << " "
				<< un->attack.returnAttack() << " " << un->radius.returnRadius() << " " << un->spr.returnSp1()		 << " "
				<< un->spr.returnSp2()		 << " " << un->XY.x					 << " " << un->XY.y					 << std::endl;
			if (un->state.is_active)
				point = i + 1;
		}
	if (game->_multiplayer)
	{
		out << game->base_2->X << " " << game->base->Y << " " << game->base->color << " " << game->base->getEster()
			<< " " << game->base->getHealth() << " " << game->base->count_units << std::endl;
		for (int j = 0; j < 3; j++) out << game->base_2->list.count_unit[j] << " "; out << std::endl;
		for (int j = 0; j < 3; j++) out << game->base_2->list.count_warlock[j] << " "; out << std::endl;
		for (int j = 0; j < 3; j++) out << game->base_2->list.count_archer[j] << " "; out << std::endl;
		for (int j = 0; j < 3; j++) out << game->base_2->list.count_warrior[j] << " "; out << std::endl;
		out << "Units" << std::endl;
		int point;
		if (game->base_2->count_units == 0)
			out << "Empty" << std::endl;
		else
			for (int i = 0; i < game->base_2->count_units; i++)
			{
				Units* un;
				un = game->base_2->getLink(i + 1);
				out << un->message << std::endl;
				out << un->name.returnName() << " " << un->color << " " << un->health.returnHealth() << " " << un->armor.returnArmor() << " "
					<< un->attack.returnAttack() << " " << un->radius.returnRadius() << " " << un->spr.returnSp1() << " "
					<< un->spr.returnSp2() << " " << un->XY.x << " " << un->XY.y << std::endl;
				if (un->state.is_active)
					point = i + 1;
			}
	}
	out << isUnitSelected << std::endl;
	out << logToFile << std::endl;
	out << logToTerminal << std::endl;
	out << withoutLog << std::endl;
	if (isUnitSelected)
	{
		out << point << " " <<selectedUnit->state.is_movie << " " << selectedUnit->state.is_skills 
			<< " " << selectedUnit->state.is_direction << " "<< selectedUnit->state.skill << std::endl;
	}
}

Memento* Originator::save(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Units* selectedUnit, int& currNumBase) {
	takeMemento(game, isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
	return new ConcreteMemento(fout);
}

void Originator::restore(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, int& currNumBase)
{
	bool multiplayer;
	int countermoves_1, countermoves_2;
	fin >> multiplayer >> countermoves_1 >> countermoves_2;
	int h, w;
	fin >> w >> h;
	std::shared_ptr<Rules> rule; 
	if (multiplayer)
	{
		rule = std::make_shared<Rule_1>();
	}
	else
	{
		rule = std::make_shared<Rule_2>();
	}
	Game<Rules>* _game = Game<Rules>::get_game(rule, w, h);
	_game->_countermoves_1 = countermoves_1;
	_game->_countermoves_2 = countermoves_2;
	_game->_multiplayer = multiplayer;
	Object* o;
	char name;
	int color;
	for (int i = 0; i <= h + 1; i++)
	{
		for (int j = 0; j <= w + 1; j++)
		{
			fin >> name;
			o = new Object(name);
			fin >> color;
			o->color = color;
			_game->field->addOnMap(j, i, o);
		}
	}
	string message;
	
	fin >> message;
	int x, y;
	fin >> name >> x >> y;
	_game->neutral->cave->setLoc(x,y);
	fin >> message;
	fin >> name >> x >> y;
	_game->neutral->tablet->setLoc(x, y);
	fin >> message;
	fin >> name >> x >> y;
	_game->neutral->ruin->setLoc(x, y);
	fin >> message;
	fin >> name >> x >> y;
	_game->neutral->pab->setLoc(x, y);
	fin >> message;
	fin >> x >> y;
	_game->base->setLoc(x, y);
	int est, he, u;
	fin >> color >> est >> he >> u;
	_game->base->setEster(est);
	_game->base->setColor(color);
	_game->base->setHealth(he);
	_game->base->count_units = u;
	for (int j = 0; j < 3; j++) fin >> _game->base->list.count_unit[j];
	for (int j = 0; j < 3; j++) fin >> _game->base->list.count_warlock[j];
	for (int j = 0; j < 3; j++) fin >> _game->base->list.count_archer[j];
	for (int j = 0; j < 3; j++) fin >> _game->base->list.count_warrior[j];
	if (_game->base->count_units != 0)
	{
		int health, armor, attack, radius, sp1, sp2;
		for (int i = 0; i <= _game->base->count_units; i++)
		{
			fin >> message;
			fin >> name;
			fin >> color >> health >> armor >> attack >> radius >> sp1 >> sp2 >> x >> y;
			if (name == 'M')
			{
				_game->base->createMagician(_game->field, _game->neutral, _game->adapter, x, y);
			}
			else if (name == 'H')
			{
				_game->base->createHealer(_game->field, _game->neutral, _game->adapter, x, y);
			}
			else if (name == 'F')
			{
				_game->base->createSwordsman(_game->field, _game->neutral, _game->adapter, x, y);
			}
			else if (name == 'G')
			{
				_game->base->createSpear(_game->field, _game->neutral, _game->adapter, x, y);
			}
			else if (name == 'A')
			{
				_game->base->createArcher(_game->field, _game->neutral, _game->adapter, x, y);
			}
			else if (name == 'L')
			{
				_game->base->createArbalester(_game->field, _game->neutral, _game->adapter, x, y);
			}
			_game->base->getLink(i)->armor.setAtrib(armor);
			_game->base->getLink(i)->attack.setAtrib(attack);
			_game->base->getLink(i)->color = color;
			_game->base->getLink(i)->radius.setAtrib(radius);
			_game->base->getLink(i)->spr.setAtrib(sp1);
			_game->base->getLink(i)->spr.setAtrib(sp2);
		}
	}
	if (_game->_multiplayer)
	{
		fin >> color >> est >> he >> u;
		_game->base_2->setEster(est);
		_game->base_2->setColor(color);
		_game->base_2->setHealth(he);
		_game->base_2->count_units = u;
		
		for (int j = 0; j < 3; j++) fin >> _game->base_2->list.count_unit[j];
		for (int j = 0; j < 3; j++) fin >> _game->base_2->list.count_warlock[j];
		for (int j = 0; j < 3; j++) fin >> _game->base_2->list.count_archer[j];
		for (int j = 0; j < 3; j++) fin >> _game->base_2->list.count_warrior[j];
		if (_game->base->count_units != 0)
		{
			int health, armor, attack, radius, sp1, sp2;
			for (int i = 0; i <= _game->base_2->count_units; i++)
			{
				fin >> message;
				fin >> name;
				fin >> color >> health >> armor >> attack >> radius >> sp1 >> sp2 >> x >> y;
				if (name == 'M')
				{
					_game->base_2->createMagician(_game->field, _game->neutral, _game->adapter, x, y);
				}
				else if (name == 'H')
				{
					_game->base_2->createHealer(_game->field, _game->neutral, _game->adapter, x, y);
				}
				else if (name == 'F')
				{
					_game->base_2->createSwordsman(_game->field, _game->neutral, _game->adapter, x, y);
				}
				else if (name == 'G')
				{
					_game->base_2->createSpear(_game->field, _game->neutral, _game->adapter, x, y);
				}
				else if (name == 'A')
				{
					_game->base_2->createArcher(_game->field, _game->neutral, _game->adapter, x, y);
				}
				else if (name == 'L')
				{
					_game->base_2->createArbalester(_game->field, _game->neutral, _game->adapter, x, y);
				}
				_game->base_2->getLink(i)->armor.setAtrib(armor);
				_game->base_2->getLink(i)->attack.setAtrib(attack);
				_game->base_2->getLink(i)->color = color;
				_game->base_2->getLink(i)->radius.setAtrib(radius);
				_game->base_2->getLink(i)->spr.setAtrib(sp1);
				_game->base_2->getLink(i)->spr.setAtrib(sp2);
			}
		}
	}
	fin >> isUnitSelected;
	fin >> logToFile;
	fin >> logToTerminal;
	fin >> withoutLog;
	fin >> currNumBase;
	game = _game;
	if (isUnitSelected)
	{
		int point;
		int skill;
		bool is_movie, is_skills, is_direction;
		fin >> point >> is_movie >> is_skills >> is_direction >> skill;
		game->base->getLink(point)->state.is_active = true;
		game->base->getLink(point)->state.is_movie = is_movie;
		game->base->getLink(point)->state.is_skills = is_skills;
		game->base->getLink(point)->state.is_direction = is_direction;
		game->base->getLink(point)->managment(game->field, game->base->getAllUnits(), game->neutral, game->adapter);

	}
	else
		game->control(game->base, game->_countermoves_1);
}


Originator::~Originator() {
	out.close();
	fin.close();
}