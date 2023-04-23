#include "Base.h"

Base::Base(int size, char type, LoggerProxy* logger) {
	baseHealth = 0;
	max = 4;
	currentOrcsNum = 0;
	currentMEnum = 0;
	sizeOfField = size;
	typeOfBase = type;
	this->logger = logger;
}

Base::~Base() {

}

void Base::addInOrcsBase(string& character, Field& f1, int G) {
	if (currentOrcsNum >= max) {
		cout << "На базе максимальное количество юнитов!\n";
		system("pause");
		return;
	}

	Warrior w;
	for (int i = G - 3; i < G; i++) {
		bool isBreak = false;

		for (int j = G - 3; j < G; j++) {
			if (f1.isCellFree(i, j)) {
				w = f1.add(character, i, j);
				isBreak = true;
				break;
			}
		}

		if (isBreak) break;
	}

	*logger << "#BASE: Добавление на базу орков юнита \"" << character << "\"" << Logger::Endl();

	w.addObserver(this);
	w.un = fuf.getUnitNum(vOrcs.size() - 1);
	vOrcs.push_back(w);

	baseHealth += 30;       //при добавлении нового юнита здоровье базы увеличивается на 30
	currentOrcsNum++;
}

void Base::createOrcsBase(int G, Field& f1) {
	string z = "###";
	for (int i = G - 4; i < G; i++) {
		f1.changeCell(z, i, G - 4);
	}
	for (int j = G - 3; j < G; j++) {
		f1.changeCell(z, G - 4, j);
	}

	*logger << "#BASE: Создается база орков" << Logger::Endl();

	Warrior w;
	string ch = "OR";

	w = f1.add(ch, G - 1, G - 1);
	w.addObserver(this);
	w.un = fuf.getUnitNum(vOrcs.size() - 1);
	vOrcs.push_back(w);

	w = f1.add(ch, G - 2, G - 1);
	w.addObserver(this);
	w.un = fuf.getUnitNum(vOrcs.size() - 1);
	vOrcs.push_back(w);
	baseHealth = 80;     //изначальное хп базы = 20 + 2 юнита = 20 + 30*2 = 80 хп
	currentOrcsNum = 2;
	typeOfBase = 'o';
}

void Base::addInMEBase(string& character, Field& f1, int G) {
	if (currentMEnum >= max) {
		cout << "На базе максимальное количество юнитов!\n";
		system("pause");
		return;
	}

	Warrior w;

	for (int i = G - 3; i < G; i++) {
		bool isBreak = false;
		for (int j = 0; j < G - (G - 2); j++) {
			if (f1.isCellFree(i, j)) {
				w = f1.add(character, i, j);
				isBreak = true;
				break;
			}
		}

		if (isBreak) break;
	}

	*logger << "#BASE: Добавление на базу людей и эльфов юнита \"" << character << "\"" << Logger::Endl();

	w.addObserver(this);
	w.un = fuf.getUnitNum(vME.size() - 1);
	vME.push_back(w);

	baseHealth += 30;       //при добавлении нового юнита здоровье базы увеличивается на 30
	currentMEnum++;
}

void Base::createMEBase(int G, Field& f1) {
	string z = "###";
	for (int i = G - 4; i < G; i++) {
		f1.changeCell(z, i, G - (G - 3));
	}
	for (int j = 0; j < G - (G - 3); j++) {
		f1.changeCell(z, G - 4, j);
	}

	Warrior w;
	string ch = "EA";

	*logger << "#BASE: Создается база людей и эльфов" << Logger::Endl();

	w = f1.add(ch, G - 1, 0);
	w.addObserver(this);
	w.un = fuf.getUnitNum(vME.size() - 1);
	vME.push_back(w);

	w = f1.add(ch, G - 2, 0);
	w.addObserver(this);
	w.un = fuf.getUnitNum(vME.size() - 1);
	vME.push_back(w);
	baseHealth = 80;
	currentMEnum = 2;
	typeOfBase = 'm';
}

void Base::updateNotify(Subject* s) {
	for (int i = 0; i < vOrcs.size(); i++) {
		if (s == &(vOrcs[i])) {
			vOrcs.erase(vOrcs.begin() + i);
			currentOrcsNum--;
			s->removeObserver(this);
			return;
		}
	}

	for (int i = 0; i < vME.size(); i++) {
		if (s == &(vME[i])) {
			vME.erase(vME.begin() + i);
			currentMEnum--;
			s->removeObserver(this);
			return;
		}
	}
}

void Base::printBaseCondition() {
	if (baseHealth == 0) {
		if (currentMEnum == 0 && typeOfBase == 'm') cout << "Базы людей и эльфов нет\n";
		else if (currentOrcsNum == 0 && typeOfBase == 'o') cout << "Базы орков нет\n";
	}

	if (currentMEnum != 0 && typeOfBase == 'm') {
		cout << "Здоровье базы людей и эльфов: " << baseHealth << " HP\n";
		cout << "На базе " << currentMEnum << " людей и эльфов:\n";
		for (int i = 0; i < vME.size(); i++) {
			cout << "Персонаж на базе " << vME[i].GetValue() << ": здоровье - " << vME[i].GetHealth() <<
				", броня - " << vME[i].GetArmor() << ", урон - " << vME[i].GetDamage() << endl;
		}
	}

	if (currentOrcsNum != 0 && typeOfBase == 'o') {
		cout << "Здоровье базы орков: " << baseHealth << " HP\n";
		cout << "На базе " << currentOrcsNum << " орков:\n";
		for (int i = 0; i < vOrcs.size(); i++) {
			cout << "Персонаж на базе " << vOrcs[i].GetValue() << ": здоровье - " << vOrcs[i].GetHealth() <<
				", броня - " << vOrcs[i].GetArmor() << ", урон - " << vOrcs[i].GetDamage() << endl;
		}
	}
}
