#include "stdafx.h"
#include "Card.h"

Card::Character::Character() : general(NULL), local(NULL) {
}

Card::Character::Character(const int general, int local ) : general(general), local(local) {
}

Card::Character::~Character() {
}

Card::Character& Card::Character::operator=(Character character) {
	return Character(character.general, character.local);
}

bool& Card::Character::operator==(Character character) {	
	bool a = (general == character.general);
	return a;
}

bool& Card::Character::operator<(Character character) {
	bool a = (general < character.general);
	return a;
}

bool& Card::Character::operator>(Character character) {
	bool a = (general > character.general);
	return a;
}

bool& Card::Character::operator<=(Character character) {
	bool a = (general <= character.general);
	return a;
}

bool& Card::Character::operator>=(Character character) {
	bool a = (general >= character.general);
	return a;
}

bool Card::isEmptyCharacter(Character &current) {
	return (current.general == NULL) || (current.local == NULL);
}

bool Card::isEmptyCard() {
	return (Name == "") || (ID == NULL) || (isEmptyCharacter(lvl)) || (isEmptyCharacter(Rhand)) || (isEmptyCharacter(Lhand)) || (isEmptyCharacter(HP)) || (isEmptyCharacter(Armor)) || (isEmptyCharacter(Speed));
}


Card::Card() : Name(""), ID(NULL), lvl(NULL, NULL), Rhand(NULL, NULL), Lhand(NULL, NULL), HP(NULL, NULL), Armor(NULL, NULL), Speed(NULL, NULL), race(human), elements(air), Description("") 
{}

Card::Card(int ID) : Name(""), ID(ID), lvl(0, 0), Rhand(0, 0), Lhand(0, 0), HP(0, 0), Armor(0, 0), Speed(0, 0), race(human), elements(air), Description("") 
{}

Card::Card(std::string Name, const int ID, Character lvl, Character Rhand, Character Lhand, Character HP, Character Armor, Character Speed, Race race, Elements elements, std::string Description)
	: Name(Name), ID(ID), lvl(lvl), Rhand(Rhand), Lhand(Lhand), HP(HP), Armor(Armor), Speed(Speed), race(race), elements(elements), Description(Description) {}

Card::Card(std::string Name, const int ID, Character lvl, Character Rhand, Character Lhand, Character HP, Character Armor, Character Speed, int race, int elements, std::string Description)
	: Name(Name), ID(ID), lvl(lvl), Rhand(Rhand), Lhand(Lhand), HP(HP), Armor(Armor), Speed(Speed), race(Race(race)), elements(Elements(elements)), Description(Description) {}

Card::~Card()
{
}


Card& Card::operator=(Card card) {
	setID(card.getID());
	Name = card.Name;
	lvl = card.lvl;
	race = card.race;
	Rhand = card.Rhand;
	Lhand = card.Lhand;
	HP = card.HP;
	Armor = card.Armor;
	Speed = card.Speed;
	elements = card.elements;
	Description = card.Description;
	return *this;
}

bool& Card::operator==(Card card) {
	bool a = (Name == card.Name) && (ID == card.ID);
	return a;
}

bool& Card::operator<(Card card) {
	bool a = ID < card.ID;
	return a;
}

bool& Card::operator>(Card card) {
	bool a = ID > card.ID;
	return a;
}


std::string Card::getName() {
	return Name;
}

void Card::setName( std::string name) {
	Name = name;
}

std::string Card::getDescription() {
	return Description;
}

void Card::setDescription(std::string description) {
	Description = description;
}

int Card::getID() {
	return ID;
}

Card::Character Card::getCharacter(Character character) {
	return character;
}

void Card::setID(int id) {
	*(const_cast<int *>(&ID)) = id;
}

void Card::setCharacter(Character &current, int count) {
	*(const_cast<int *>(&current.general)) = count;
	current.local = count;
}

std::string Card::race_to_string(Race race) {
	switch (race)
	{
	case human:
		return "human";
	case elf:
		return "elf";
	case orc:
		return "orc";
	case goblin:
		return "goblin";
	case angel:
		return "angel";
	case gnoll:
		return "gnoll";
	case inferno:
		return "inferno";
	case undead:
		return "undead";
	default:
		break;
	}
	return NULL;
}

Card::Race Card::string_to_Race(std::string race) {
	if(race.find("human") != -1)
		return human;
	if(race.find("elf") != -1)
		return elf;
	if(race.find("orc") != -1)
		return orc;
	if(race.find("goblin") != -1)
		return goblin;
	if(race.find("angel") != -1)
		return angel;
	if(race.find("gnoll") != -1)
		return gnoll;
	if(race.find("inferno") != -1)
		return inferno;
	if(race.find("undead") != -1)
		return undead;
	return human;
}

std::string Card::get_race() {
	return race_to_string(race);
}

std::string Card::get_elem() {
	return elements_to_string(elements);
}

std::string Card::elements_to_string(Elements elements) {
	switch (elements)
	{
	case air:
		return "air";
	case fire:
		return "fire";
	case ground:
		return "ground";
	case dark:
		return "dark";
	case light:
		return "light";
	case water:
		return "water";
	default:
		break;
	}
	return NULL;
}

Card::Elements Card::string_to_Elements(std::string elements) {

	if(elements.find("air") != -1)
		return air;
	if(elements.find("fire") != -1)
		return fire;
	if(elements.find("ground") != -1)
		return ground;
	if(elements.find("dark") != -1)
		return dark;
	if(elements.find("light") != -1)
		return light;
	if(elements.find("water") != -1)
		return water;

}

Card::Character *Card::int_to_Character(int n) {
	switch (n)
	{
	case 1:
		return &lvl;
	case 2:
		return &Rhand;
	case 3:
		return &Lhand;
	case 4:
		return &HP;
	case 5:
		return &Armor;
	case 6:
		return &Speed;
	default:
		break;
	}
}

void Card::recard(std::string newName, Character newRhand, Character newLhand, Character newHP, Character newArmor, Character newSpeed, Race newrace, Elements newelements, std::string newDescription)
{
	Name = newName;
	Rhand = newRhand;
	Lhand = newLhand;
	HP = newHP;
	Armor = newArmor;
	Speed = newSpeed;
	race = newrace;
	elements = newelements;
	Description = newDescription;
}

void Card::recard(std::string newName, int newRhand, int newLhand, int newHP, int newArmor, int newSpeed, Race newrace, Elements newelements, std::string newDescription)
{
	Name = newName;
	setCharacter(Rhand, newRhand);
	setCharacter(Lhand, newLhand);
	setCharacter(HP, newHP);
	setCharacter(Armor, newArmor);
	setCharacter(Speed, newSpeed);
	race = Race(newrace);
	elements = Elements(newelements);
	Description = newDescription;
}

void Card::recard(std::string newName, int newRhand, int newLhand, int newHP, int newArmor, int newSpeed, int newrace, int newelements, std::string newDescription)
{
	Name = newName;
	setCharacter(Rhand, newRhand);
	setCharacter(Lhand, newLhand);
	setCharacter(HP, newHP);
	setCharacter(Armor, newArmor);
	setCharacter(Speed, newSpeed);
	race = Race(newrace);
	elements = Elements(newelements);
	Description = newDescription;
}

std::string Card::smth_to_filestring(std::string smth, int size) {
	std::string res = smth;
	for (int i = 0; i <= size; ++i) {
		if (smth.size() < i) {
			res += " ";
		}
	}
	res += "| ";
	return res;
}

std::string Card::Card_to_filestring() {
	int size = 0;
	std::string res = "";
	res += smth_to_filestring(std::to_string(ID), 4);
	res += smth_to_filestring(Name, 12);
	res += smth_to_filestring(std::to_string(lvl.general), 4);
	res += smth_to_filestring(std::to_string(Rhand.general), 4);
	res += smth_to_filestring(std::to_string(Lhand.general), 4);
	res += smth_to_filestring(std::to_string(HP.general), 4);
	res += smth_to_filestring(std::to_string(Armor.general), 4);
	res += smth_to_filestring(std::to_string(Speed.general), 4);
	res += smth_to_filestring(race_to_string(race), 8);
	res += smth_to_filestring(elements_to_string(elements), 8);
	res += smth_to_filestring(Description, 4);
	return res;
}

std::string Card::character_to_printstring(Character character) {
	//if (character.local <= 0) { return "0"; }
	if (character.local < character.general) return "{s(4, 0)}" + std::to_string(character.local) + "{s(15, 0)}";
	if (character.local > character.general) return "{s(1, 0)}" + std::to_string(character.local) + "{s(15, 0)}";
	return std::to_string(character.local);
}

int Card::h_to_12(std::string str, bool h) {		//(h = true) если стоит первым
	if (str.size() > 12) return 0;
	if (!h) {
		if (str.size() % 2 != 0) {
			return ((12 - str.size()) / 2 + 1);
		}
	}
	return ((12 - str.size()) / 2);
}

std::string Card::Card_to_printstring() {
	/*1*/
	std::string myCard = "";
	myCard += " ";
	for (int i = 0; i < 12; ++i) { myCard += "_"; }
	myCard += " \n";
	/*2*/
	myCard += "/";
	for (int i = 0; i < h_to_12(Name, 1); ++i) { myCard += " "; }
	myCard += Name;
	for (int i = 0; i < h_to_12(Name, 0); ++i) { myCard += " "; }
	myCard += "\\\n";
	/*3*/
	myCard += "|";
	for (int i = 0; i < h_to_12(std::to_string(lvl.local), 1); ++i) { myCard += " "; }
	myCard += character_to_printstring(lvl);
	for (int i = 0; i < h_to_12(std::to_string(lvl.local), 0); ++i) { myCard += " "; }
	myCard += "|\n";
	/*4*/
	myCard += "|";
	for (int i = 0; i < h_to_12(race_to_string(race), 1); ++i) { myCard += " "; }
	myCard += race_to_string(race);
	for (int i = 0; i < h_to_12(race_to_string(race), 0); ++i) { myCard += " "; }
	myCard += "|\n";
	/*5*/
	myCard += "|";
	for (int i = 0; i < h_to_12(std::to_string(Rhand.local) + " \\ / " + std::to_string(Lhand.local), 1) + 1; ++i) { myCard += " "; }
	myCard += character_to_printstring(Rhand);
	myCard += " \\/ ";
	myCard += character_to_printstring(Lhand);
	for (int i = 0; i < h_to_12(std::to_string(Rhand.local) + " \\ / " + std::to_string(Lhand.local), 0); ++i) { myCard += " "; }
	myCard += "|\n";
	/*6*/
	myCard += "|";
	for (int i = 0; i < h_to_12(std::to_string(HP.local), 1); ++i) { myCard += " "; }
	myCard += character_to_printstring(HP);
	for (int i = 0; i < h_to_12(std::to_string(HP.local), 0); ++i) { myCard += " "; }
	myCard += "|\n";
	/*7*/
	myCard += "|";
	for (int i = 0; i < h_to_12(std::to_string(Armor.local), 1); ++i) { myCard += " "; }
	myCard += character_to_printstring(Armor);
	for (int i = 0; i < h_to_12(std::to_string(Armor.local), 0); ++i) { myCard += " "; }
	myCard += "|\n";
	/*8*/
	myCard += "|";
	for (int i = 0; i < 12; ++i) { myCard += "-"; }
	myCard += "|\n";
	/*9*/
	myCard += "|  /";
	for (int i = 0; i < h_to_12(std::to_string(Speed.local), 1) - 3; ++i) { myCard += " "; }
	myCard += character_to_printstring(Speed);
	for (int i = 0; i < h_to_12(std::to_string(Speed.local), 0) - 3; ++i) { myCard += " "; }
	myCard += "\\  |\n";
	/*10*/
	myCard += "|";
	for (int i = 0; i < 12; ++i) { myCard += "-"; }
	myCard += "|\n";
	/*11*/
	myCard += "|";
	for (int i = 0; i < h_to_12(elements_to_string(elements), 1); ++i) { myCard += " "; }
	myCard += elements_to_string(elements);
	for (int i = 0; i < h_to_12(elements_to_string(elements), 0); ++i) { myCard += " "; }
	myCard += "|\n";
	/*12*/
	myCard += "|";
	for (int i = 0; i < 12; ++i) { myCard += "_"; }
	myCard += "|\n";

	return myCard;
}

void Card::filestring_to_Card(std::string filestring) {
	int pos = 0;
	/*ID*/
	int pos1 = filestring.find("|", pos);
	setID(stoi(filestring.substr(pos, pos1 - pos)));
	pos = pos1 + 2;
	/*Name*/
	pos1 = filestring.find("|", pos);
	setName(filestring.substr(pos, pos1 - pos));
	pos = pos1 + 2;
	/*lvl, Rhand, Lhand, HP, Armor, Speed*/
	for (int i = 1; i <= 6; ++i) {
		pos1 = filestring.find("|", pos);
		setCharacter(*int_to_Character(i), stoi(filestring.substr(pos, pos1 - pos)));
		pos = pos1 + 2;
	}
	/*race*/
	pos1 = filestring.find("|", pos);
	race = string_to_Race(filestring.substr(pos, pos1 - pos));
	pos = pos1 + 2;
	/*elements*/
	pos1 = filestring.find("|", pos);
	elements = string_to_Elements(filestring.substr(pos, pos1 - pos));
	pos = pos1 + 2;
	/*description*/
	pos1 = filestring.find("|", pos);
	Description = filestring.substr(pos, pos1 - pos);
}

void Card::character_up(Character &current, int up) {
	current.local += up;
	if (current.local < 0) current.local = 0;
}

void Card::character_change(Character &current, int count) {
	if (count < 0) return;
	current.local = count;
}

