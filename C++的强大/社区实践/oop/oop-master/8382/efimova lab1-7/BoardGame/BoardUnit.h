#pragma once
class BoardUnit
{
public:
	struct ActionMeta {
		BoardUnit* fromUnit = nullptr; //из нашего юнита
		BoardUnit* toUnit = nullptr; //в юнит

		bool isMove = false; 
		unsigned int moveX = 0;
		unsigned int moveY = 0;

		bool isHeal = false;
		unsigned int hpHeal = 0;
		unsigned int armorBuff = 0;

		bool isAttack = false;
		unsigned int hpAttack = 0;
		unsigned int armorAttack = 0;
	};
	BoardUnit();
	~BoardUnit();
	virtual BoardUnit* getCopy() = 0; //копирование
	virtual ActionMeta turnAction() = 0; //между ходами игроков
	virtual bool isAttackable() = 0; //структура происход. действий
	static unsigned int getUnitCount(); //считаем все юниты
private:
	static unsigned int unitCount; //считаем наш юнит
};

