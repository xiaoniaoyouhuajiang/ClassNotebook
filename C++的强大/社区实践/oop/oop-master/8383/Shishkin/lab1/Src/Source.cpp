#include <iostream>
#include <iomanip>
#include "Warrior.h"
#include "Orcs.h"
#include "Men.h"
#include "Elfs.h"
#include "Field.h"
#include "Iterator.h"

using namespace std;

int scan(int& numOfOrcs, int& numOfMens, int& numOfElfs, int& G);

int main() {
	setlocale(LC_ALL, "RUS");

	int G;
	string st;

	int numOfOrcs;
	int numOfMens;
	int numOfElfs;

	if (scan(numOfOrcs, numOfMens, numOfElfs, G) == 0) {
		cout << "Ошибка!\n";
		system("pause");
		return 0;
	}
	cout << numOfOrcs << endl << numOfMens << endl << numOfElfs << endl << G << endl;

	Field f1(G);
	f1.init(numOfOrcs, numOfElfs, numOfMens);

	int k = 0;
	int direction;
	do {
		system("cls");
		st.clear();
		f1.print();
		int forAddAndDel = 0;
		if (k % 2 == 0) {
			cout << "1-й игрок, ваш ход:\n";
			cout << "Введите персонажа из эльфов или людей:\n";
			cin >> st;
			if (st == "exit") break;
			else if (st == "add") {
				forAddAndDel = 1;
				cout << "Введите обозначение персонажа, которого вы хотите добавить:\n";
				string character;
				cin >> character;
				if (character != "OD" && character != "OR" && character != "MS" && character != "MW" && character != "EA" && character != "EI") {
					cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
					system("pause");
				}
				else {
					f1.add(character);
				}
			}
			else if (st == "del") {
				forAddAndDel = 1;
				cout << "Введите обозначение персонажа, которого вы хотите удалить:\n";
				string character;
				cin >> character;
				f1.del(character);
			}
			else
			while (st[0] == 'O') {
				cout << "Неверно! Вы играете за эльфов и людей!\n";
				cin >> st;
			}
		}
		else {
			cout << "2-й игрок, ваш ход:\n";
			cout << "Введите персонажа из орков:\n";
			cin >> st;
			if (st == "exit") break;
			else if (st == "add") {
				forAddAndDel = 1;
			}
			else if (st == "del") {
				forAddAndDel = 1;
				cout << "Введите обозначение персонажа, которого вы хотите удалить:\n";
				string character;
				cin >> character;
				f1.del(character);
			}
			else
			while (st[0] == 'M' || st[0] == 'E') {
				cout << "Неверно! Вы играете за орков!\n";
				cin >> st;
			}
		}
		if (forAddAndDel == 0) {
			getchar();
			cout << "Введите направление:\n";
			string opportunity = f1.check(st);
			cin >> direction;

			char tmp = direction + '0';
			int checker = 0;
			for (int i = 0; i < opportunity.length(); i++) {
				if (opportunity[i] == tmp) checker = 1;
			}

			if (checker == 1) f1.moving(st, direction);
			else {
				cout << "Такого направления нет! Вы пропускаете ход!\n";
				system("pause");
			}
		}
		k++;
	} while (st != "exit");

	system("pause");
	return 0;

}

int scan(int& numOfOrcs, int& numOfMens, int& numOfElfs, int& G) {
	cout << "Вам предложено ввести количество орков, эльфов и людей.\n";
	cout << "Так как в игре 2 игрока: один за орков, а другой за людей и эльфов, то\n";
	cout << "количество людей и эльфов должно соответствовать количеству окров.\n";
	cout << "(Первый игрок за людей и эльфов, второй - за орков. 4 < Кол-во орков < 10)\n\n";

	cout << "Введите количество людей:\n";
	cin >> numOfMens;
	if (cin.fail() || numOfMens <= 0) {
		return 0;
	}

	cout << "Введите количество эльфов:\n";
	cin >> numOfElfs;
	if (cin.fail() || numOfElfs <= 0) {
		return 0;
	}

	numOfOrcs = numOfElfs + numOfMens;

	if (numOfOrcs <= 4 || numOfOrcs >= 10) return 0;

	cout << "Создается поле размерностью GxG. Введите G:\n";
	cin >> G;

	if (cin.fail()) {
		return 0;
	}
	while (G <= numOfOrcs - 1) {
		cout << "G введено неверно! Оно должно быть больше " << numOfOrcs - 1 << endl;
		cin >> G;
	}

	return 1;
}
