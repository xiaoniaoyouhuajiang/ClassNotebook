#include "NeutralObject.h"

//Health_ID = 0, Armor_ID, Killer_ID, Freezer_ID

NeutralObject* NeutralObject::create(NeutralObject_ID id) {
	NeutralObject* no;

	switch (id) {
	case Health_ID:
		no = new HealthReplenishment();
		break;

	case Armor_ID:
		no = new ArmorReplenishment();
		break;

	case Killer_ID:
		no = new Killer();
		break;

	case Freezer_ID:
		no = new Freezer();
		break;

	default:
		no = nullptr;
	}

	return no;
}

//-----------------------------------------------------------

string HealthReplenishment::getNeutObjType() {
	return "HealthR";
}

void HealthReplenishment::operator+=(Warrior* w) {
	char a = (*(w)).GetValue()[0];
	char b = (*(w)).GetValue()[1];

	string str = "";
	str.push_back(a);
	str.push_back(b);

	if (str == "EA" || str == "EI") {
		(*(w)).SetHealth(50);
		cout << "Вы попали на блок, который восстанавливает здоровье (юнит " << (*(w)).GetValue() << ")\n";
	}
	else if (str == "MS" || str == "MW") {
		(*(w)).SetHealth(25);
		cout << "Вы попали на блок, который восстанавливает здоровье (юнит " << (*(w)).GetValue() << ")\n";
	}
	else if (str == "OD" || str == "OR") {
		(*(w)).SetHealth(100);
	}
}

//-----------------------------------------------------------

string ArmorReplenishment::getNeutObjType() {
	return "ArmorR";
}

void ArmorReplenishment::operator+=(Warrior* w) {
	char a = (*(w)).GetValue()[0];
	char b = (*(w)).GetValue()[1];

	string str = "";
	str.push_back(a);
	str.push_back(b);

	if (str == "EA" || str == "EI") {
		(*(w)).SetArmor(12);
		cout << "Вы попали на блок, который восстанавливает броню (юнит " << (*(w)).GetValue() << ")\n";
	}
	else if (str == "MS" || str == "MW") {
		(*(w)).SetArmor(50);
		cout << "Вы попали на блок, который восстанавливает броню (юнит " << (*(w)).GetValue() << ")\n";
	}
	else if (str == "OD" || str == "OR") {
		(*(w)).SetArmor(8);
		cout << "Вы попали на блок, который восстанавливает броню (юнит " << (*(w)).GetValue() << ")\n";
	}
}

//-----------------------------------------------------------

string Killer::getNeutObjType() {
	return "Killer";
}

void Killer::operator+=(Warrior* w) {
	cout << "Вы попали на блок Killer\n";
	(*w).SetHealth(5);
}

//-----------------------------------------------------------

string Freezer::getNeutObjType() {
	return "Freezer";
}

void Freezer::operator+=(Warrior* w) {
	cout << "Вы попали на блок Freezer\n";
	(*w).SetAbilityToWalk(2);
}
