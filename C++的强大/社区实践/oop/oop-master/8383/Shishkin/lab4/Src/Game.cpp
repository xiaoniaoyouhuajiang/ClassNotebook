#include "Game.h"

//void Game::start() {
Game::Game() {
	int G;
	string st;         //через эту переменную происходит считывание данных пользователя

	int numOfOrcs;
	int numOfMens;
	int numOfElfs;

	int howToLog = 0;	//для выбора логирования
	logger = new LoggerProxy();
	cout << "Выберите формат логирования:\n";
	cout << "1 - Логирование в файл\n2 - Логирование в терминал\n3 - Без логирования\n";
	cin >> howToLog;

	switch (howToLog) {
	case 1:
		setLogger(new LoggingFile("log.txt"));
		break;

	case 2:
		setLogger(new LoggingTerminal());
		break;

	case 3:
		setLogger(new NoLogging());
		break;

	default:
		cout << "Так как был выбран неверный формат логирования, то его не будет\n";
		setLogger(new NoLogging());
		break;
	}


	if (scan(numOfOrcs, numOfMens, numOfElfs, G) == 0) {
		cout << "Ошибка!\n";
		system("pause");
		return;
	}

	*logger << "#GAME: Создана игра с размером поля " << G << "; количество орков - " << numOfOrcs << "; количество людей - " << numOfMens << Logger::Endl();

	Base MEb(G, 'm', logger);
	bool isMEbaseExist = false;     //чтобы не создавать базу повторно
	Base b(G, 'o', logger);
	bool isObaseExist = false;     //чтобы не создавать базу повторно

	Field f1(G, numOfOrcs, logger);
	f1.init(numOfOrcs, numOfElfs, numOfMens);

	int k = 0;
	//int direction;
	Iterator it(f1.getCell(), G, G);
	do {
		system("cls");
		st.clear();
		f1.print();
		int forAddAndDel = 0;


		//---------------------------------------------------------------------
		//       1-Й ИГРОК
		//---------------------------------------------------------------------


		if (k % 2 == 0) {
			cout << "1-й игрок, ваш ход:\n";
			cout << "Введите персонажа из эльфов или людей:\n";
			cin >> st;

			if (st == "exit") break;

			else if (st == "add") {
				forAddAndDel = 1;
				if (!addUnit(f1)) continue;
			}

			else if (st == "del") {
				delUnit(f1);
				forAddAndDel = 1;
			}

			else if (st == "base") {
				forAddAndDel = 1;
				cout << "Введите \"create\", чтобы создать базу, либо \"add\", чтобы добавить юнита в базу" << endl;
				cin >> st;

				if (st == "create" && !isMEbaseExist) {
					isMEbaseExist = true;
					//MEb.createMEBase(G, f1);
					CommandBase cb(&f1, &MEb, "createME");
					string tmp = "";
					cb.execute(tmp);
				}

				else if (st == "add") {
					cout << "Введите обозначение персонажа, которого вы хотите добавить:\n";
					string character;
					cin >> character;
					if (character != "MS" && character != "MW" && character != "EA" && character != "EI") {
						cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
						system("pause");
					}
					else {
						//MEb.addInMEBase(character, f1, G);
						CommandBase cb(&f1, &MEb, "addInME");
						cb.execute(character);
					}
				}
			}

			else
				while (st[0] == 'O') {
					cout << "Неверно! Вы играете за эльфов и людей!\n";
					cin >> st;
				}
		}


		//---------------------------------------------------------------------
		//       2-Й ИГРОК
		//---------------------------------------------------------------------


		else {
			cout << "2-й игрок, ваш ход:\n";
			cout << "Введите персонажа из орков:\n";
			cin >> st;
			if (st == "exit") break;
			else if (st == "add") {
				forAddAndDel = 1;
				if (!addUnit(f1)) continue;
			}
			else if (st == "del") {
				forAddAndDel = 1;
				delUnit(f1);
			}
			else if (st == "base") {
				forAddAndDel = 1;
				cout << "Введите \"create\", чтобы создать базу, либо \"add\", чтобы добавить юнита в базу" << endl;
				cin >> st;
				if (st == "create" && !isObaseExist) {
					isObaseExist = true;
					//b.createOrcsBase(G, f1);
					CommandBase cb(&f1, &b, "createO");
					string tmp = "";
					cb.execute(tmp);
				}
				else if (st == "add") {
					cout << "Введите обозначение персонажа, которого вы хотите добавить:\n";
					string character;
					cin >> character;
					if (character != "OD" && character != "OR") {
						cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
						system("pause");
					}
					else {
						//b.addInOrcsBase(character, f1, G);
						CommandBase cb(&f1, &b, "addInO");
						cb.execute(character);
					}
				}
			}
			else
				while (st[0] == 'M' || st[0] == 'E') {
					cout << "Неверно! Вы играете за орков!\n";
					cin >> st;
				}
		}

		//       ХОД ЗА ЮНИТА

		if (forAddAndDel == 0) {
			unitMove(f1, st);

			int numOfMoves = f1.howManyMoves(st);
			for (int l = 0; l < numOfMoves; l++) {
				f1.landscapeEffect();
				f1.neutObjEffect();
				cout << "Вы можете сделать еще один ход за своего персонажа\n";
				string ch;
				cin >> ch;
				unitMove(f1, ch);
			}
		}
		f1.landscapeEffect();
		f1.neutObjEffect();

		k++;

		cout << "\nВведите \"info\", чтобы вывести информацию о юнитах и базе; Введите что угодно, чтобы ничего не выводить\n";
		cin >> st;
		if (st == "info") {
			it.displayUnitData(f1);
			cout << endl;
			MEb.printBaseCondition();
			b.printBaseCondition();
			system("pause");
		}
	} while (st != "exit");
	*logger << "#GAME: Game over!" << Logger::Endl();

	delete logger;
}

int Game::scan(int& numOfOrcs, int& numOfMens, int& numOfElfs, int& G) {
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
	while (G <= numOfOrcs + 3) {
		cout << "G введено неверно! Оно должно быть больше " << numOfOrcs + 3 << endl;
		cin >> G;
	}

	return 1;
}

void Game::unitMove(Field& f, string character) {
	int direction = 0;
	getchar();
	cout << "Введите направление:\n";
	string opportunity = f.check(character);

	cin >> direction;

	char tmp = direction + '0';
	int checker = 0;
	for (int i = 0; i < (int)opportunity.length(); i++) {
		if (opportunity[i] == tmp) checker = 1;
	}

	if (checker == 1) {
		CommandField cf(&f, "move");
		string forMove = character + tmp;
		cf.execute(forMove);
		//f.moving(character, direction);
		*logger << "#GAME: Передвежение юнита \"" << character << "\" по направлению " << direction << Logger::Endl();
	}
	else {
		cout << "Такого направления нет! Вы пропускаете ход!\n";
	}
}

bool Game::addUnit(Field& f) {
	cout << "Введите обозначение персонажа, которого вы хотите добавить:\n";
	string character;
	cin >> character;
	getchar();
	if (character != "OD" && character != "OR" && character != "MS" && character != "MW" && character != "EA" && character != "EI") {
		cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
		system("pause");
		return false;
	}
	else {
		//f.add(character, -30, 0);
		CommandField cf(&f, "add");
		cf.execute(character);
		*logger << "#GAME: Добавление юнита \" " << character << "\"" << Logger::Endl();
	}

	return true;
}

void Game::delUnit(Field& f) {
	cout << "Введите обозначение персонажа, которого вы хотите удалить:\n";
	string character;
	cin >> character;
	//f.del(character);
	CommandField cf(&f, "del");
	cf.execute(character);
	*logger << "#GAME: Удаление юнита \" " << character << "\"" << Logger::Endl();
}

void Game::setLogger(Logger* logger_) { 
	logger->setLogger(logger_); 
}

void Game::setLogFormatter(LogFormatter* formatter) {
	logger->setFormat(formatter);
}
