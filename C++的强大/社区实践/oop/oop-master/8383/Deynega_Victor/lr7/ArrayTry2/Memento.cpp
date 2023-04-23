#include "Memento.h"
#include <iostream>

Memento::Memento(std::string message, bool flag) {
	std::string saveName;
	std::cout << "\nType name of save:\n";
	if (!flag) {
		std::cin >> saveName;
		saveName += ".txt";
		filePtr = new File(saveName);
		filePtr->write(message);
		filePtr->file.close();
	}
	else {
		std::cin >> saveName;
		saveName += ".txt";
		filePtr = new File(saveName, true);
		if (!filePtr->isOpen()) {
			saveString = "NULL";
		}
		else {
			filePtr->read(saveString);
		}
	}
}




bool Memento::isValid() {
	int unitCounter = 0;
	if (saveString[0] != '0' || saveString[1] != '_') return false; //wrong structure
	int pos = 2;
	int res = this->getNum(pos);
	if (res < 3 || res > 14) return false; //wrong size(optional)
	if (saveString[pos] != '\n' || saveString[pos+1] != '\t') return false; //wrong structure
	pos+=2;
	int startOfField = pos;
	for (int i = 0; i < res; i++) {
		for (int j = 0; j < res; j++) {
			std::vector<int> info;
			getNum(pos, info);
			if (info.size() != 3) return false; //wrong info string
			if (info[0] != 0 && info[1] != 0) return false; //if units stay on lake/mountain
			if ((info[2] != 0 && info[2] != 1 && info[2] != 2 && info[2] != 3 && info[2] != 4)
				|| (info[0] != 0 && info[0] != 1 && info[0] != 2)
				|| (info[1] != 0 && info[1] != 1 && info[1] != 2 && info[1] != 3 && info[1] != 4 && info[1] != 5 && info[1] != 6)) return false;
			if (info[1] != 0) unitCounter++;
			pos -= 1;
			if ((i * j) == (res - 1) * (res - 1)) {
				if (saveString[pos] != '\n' || saveString[pos+1] != '1' || saveString[pos+2] != '_') return false;
			}
			else {
				if (saveString[pos] != '_') return false; //wrong structure
			}
			info.clear();
			pos++;
		}
	}
	pos += 2;
	int baseX = getNum(pos);
	if (baseX >= res-1) return false;
	pos++;
	int baseY = getNum(pos);
	if (baseY >= res-1) return false;
	pos++;
	if(getNum(pos) < 0) return false; //health < 0;
	pos++;
	int units = getNum(pos);
	if (units < 0 || units >(res * res / 2)) return false;
	pos++;
	int numOfUnits = getNum(pos);
	if (numOfUnits < 0 || numOfUnits > units) return false;
	if (saveString[pos] != '\n') return false;
	if (numOfUnits != unitCounter) return false;
	std::vector<int> info;
	startOfField = 4 * (baseY * res + baseX) + startOfField;
	getNum(startOfField, info);
	if (info[1] != 0) return false;
	return true;
}


int Memento::getNum(int& pos) {
	int num = 0;
	std::string tmp;
	while (saveString[pos] >= 48 && saveString[pos] <= 57) {
		tmp += saveString[pos];
		pos++;
	}
	std::string::size_type sz;
	if (tmp.length() == 0) {
		return -1;
	}
	return stoi(tmp, &sz);
}


void Memento::getNum(int& pos, std::vector<int>& info) {
	int num = 0;
	//info.resize(4);
	while (saveString[pos] >= 48 && saveString[pos] <= 57) {
		info.push_back(saveString[pos] - 48);
		pos++;
	}
	pos++;
}


Memento::~Memento() {
	delete filePtr;
}