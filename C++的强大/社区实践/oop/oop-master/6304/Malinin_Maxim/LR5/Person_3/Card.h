#pragma once
#include "iostream"
#include <string>
#include <Windows.h>



class Card
{
private:
	enum Elements
	{
		air,
		fire,
		ground,
		water,
		light,
		dark
	};

	enum Race
	{
		human,
		elf,
		orc,
		goblin,
		angel,
		gnoll,
		inferno,
		undead
	};

	enum ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
	
	struct Character {
		const int general;						//изначальна€ характеристика
		int local;								//с возможными изменени€ми

		Character();
		~Character();
		Character(const int general, int local);

		Character& operator=( Character character);
		bool& operator==(Character character);
		bool& operator>(Character character);
		bool& operator<(Character character);
		bool& operator>=(Character character);
		bool& operator<=(Character character);
	};

	std::string Name;						//»м€
	const int ID;							//ID карты

	Character lvl;							//уровень
	Character Rhand;						//урон правой рукой
	Character Lhand;						//урон левой рукой
	Character HP;							//количество жизни
	Character Armor;						//брон€
	Character Speed;						//скорость

	Race race;								//раса
	Elements elements;						//стихи€
	std::string Description;				//описание


public:

	Card();
	Card(std::string Name, const int ID, Character lvl, Character Rhand, Character Lhand, Character HP, Character Armor, Character Speed, Race race, Elements elements, std::string Description);
	Card(std::string Name, const int ID, Character lvl, Character Rhand, Character Lhand, Character HP, Character Armor, Character Speed, int race, int elements, std::string Description);
	Card(int ID);
	~Card();

	Card& operator=(Card card);
	bool& operator==(Card card);
	bool& operator<(Card card);
	bool& operator>(Card card);

	std::string race_to_string(Race race);							//перевод рассы в стринг
	Race string_to_Race(std::string filerace);						//ѕеревод из string в race
	std::string elements_to_string(Elements elements);				//перевод елемента в стринг
	Elements string_to_Elements(std::string elements);				//ѕеревод из string в elements

	Character *int_to_Character(int n);								//1 - lvl, 2 - Rhand, 3 - Lhand, 4 - HP, 5 - Armor, 6 - Speed
	std::string smth_to_filestring(std::string smth, int size);		//ѕеревод любой характеристики в string с отступом до |
	std::string Card_to_filestring();								//ѕеревод карты в string
	std::string character_to_printstring(Character character);

	int h_to_12(std::string str, bool h);
	std::string Card_to_printstring();
	void filestring_to_Card(std::string filestring);				//„тение карты из строки 

	std::string getName();											//ѕолучить им€ карты
	void setName(std::string name);									//»зменить им€ карты
	std::string getDescription();
	void setDescription(std::string description);
	int getID();													//ѕолучить ID карты
	void setID(int id);												//»зменить ID карты
	Character getCharacter(Character character);					//ѕолучить характристику карты
	void setCharacter(Character &current, int count);				//»зменить характеристику карты

	std::string get_race();
	std::string get_elem();

	void recard(std::string newName, Character newRhand, Character newLhand, Character newHP, Character newArmor, Character newSpeed, Race newrace, Elements newelements, std::string newDescription);
	void recard(std::string newName, int newRhand, int newLhand, int newHP, int newArmor, int newSpeed, int newrace, int newelements, std::string newDescription);
	void recard(std::string newName, int newRhand, int newLhand, int newHP, int newArmor, int newSpeed, Race newrace, Elements newelements, std::string newDescription);
	

	bool Card::isEmptyCharacter(Character &current);				//провер€ет character == NULL
	bool Card::isEmptyCard();										//провер€ет card == NULL

	void character_up(Character &current, int up);					//измен€ет характеристику на +up
	void character_change(Character &current, int up);				//измен€ет характеристику на up


};