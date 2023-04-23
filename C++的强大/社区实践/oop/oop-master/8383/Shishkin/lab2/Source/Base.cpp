#include "Base.h"

Base::Base(int size) {
	baseHealth = 100;
	max = 4;
	currentOrcsNum = 0;
	currentMEnum = 0;
	sizeOfField = size;
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

	w.addObserver(this);
	w.un = fuf.getUnitNum(vOrcs.size() - 1);
	vOrcs.push_back(w);

	baseHealth += 10;       //при добавлении нового юнита здоровье базы увеличивается на 10
	currentOrcsNum++;
}

void Base::createOrcsBase(int G, Field& f1, int numOfUnits) {
	string z = "###";
	for (int i = G - 4; i < G; i++) {
		f1.changeCell(z, i, G - 4);
	}
	for (int j = G - 3; j < G; j++) {
		f1.changeCell(z, G - 4, j);
	}

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
	baseHealth = 30;
	currentOrcsNum = 2;
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

	w.addObserver(this);
	w.un = fuf.getUnitNum(vME.size() - 1);
	vME.push_back(w);

	baseHealth += 10;       //при добавлении нового юнита здоровье базы увеличивается на 10
	currentMEnum++;
}

void Base::createMEBase(int G, Field& f1, int numOfUnits) {
	string z = "###";
	for (int i = G - 4; i < G; i++) {
		f1.changeCell(z, i, G - (G - 3));
	}
	for (int j = 0; j < G - (G - 3); j++) {
		f1.changeCell(z, G - 4, j);
	}

	Warrior w;
	string ch = "EA";

	w = f1.add(ch, G - 1, 0);
	w.addObserver(this);
	w.un = fuf.getUnitNum(vME.size() - 1);
	vME.push_back(w);

	w = f1.add(ch, G - 2, 0);
	w.addObserver(this);
	w.un = fuf.getUnitNum(vME.size() - 1);
	vME.push_back(w);
	baseHealth = 30;
	currentMEnum = 2;
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
