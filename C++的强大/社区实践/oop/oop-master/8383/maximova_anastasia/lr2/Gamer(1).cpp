#include "Gamer.h"

Gamer::Gamer() {
	name = '0';
	answer = team1 = team2 = '0';
	exit = height = width = 0;
	y2 = y = x2 = x = 0;
}

int Gamer::dataCorrect() { //функция, проверяющая корректность входных данных (ожидается число)
	int a = 0;

	while (!(cin >> a)) {
		cout << "Ошибка. Данные некорректны! Ожидается число." << endl;
		cin.clear();     //сброс коматозного состояние cin
		cin.ignore(1000, '\n');
		fflush(stdin);   //очистка потока ввода
	}
	cin.get();
	return a;
}

void Gamer::caseField() {
	system("color 79");
	cout << endl << "Перед началом игры введите высоту и ширину игрового поля.\n";
	height = dataCorrect();
	width = dataCorrect();
	if (height <= 3 || width <= 3) {
		cout << "Ошибка: неверно указан размер поля!\nСоздано поле стандартного размера.\n";
		width = height = 10;
	}
	field = new GameField(height, width);
	casePrintField();
	cout << "Построено поле высоты: " << field->getHeight() << " и ширины: " << field->getWidth() << ".\n";
}

void Gamer::caseName(int numberGamer) {
	cout << "Игрок №" << numberGamer << ", введите ваше имя (допустимая длина 20 символов).\n";
	cin >> name;

	if (numberGamer == 1) {
		cout << name << ", выберите за какую команду вы будете играть.\n";
		cout << "Если вы хотите играть за монстров введите \"m\".\n";
		cout << "Если вы хотите играть за героев введите \"h\".\n";
		if (!choice2()) team1 = 'h';
		else team1 = 'm';
	}
	else {
		cout << "Ваша команда ";
		if (team1 == 'h') {
			team2 = 'm';
			cout << " монстры.\n";
		}
		else {
			team2 = 'h';
			cout << " герои.\n";
		}
	}
	casePrintField();
}

bool Gamer::choice2() {
	do {
		exit = 0;
		cin >> answer;
		answer = tolower(answer);

		switch (answer) {
		case 'm':
			return 1;
			break;

		case 'h':
			return 0;
			break;

		default:
			cout << "Ошибка: введен неккоректный символ. Попробуйте еще раз.\n";
			exit = 1;
		}
	} while (exit == 1); 
}

void Gamer::addUnitRandom(char type) {
	int view, i;
	srand(time(NULL));
	if (field->getBase(type)->getCounterUnits() < field->getBase(type)->getmaxUnitsSt()) {
	
		if (field->getBase(type)->getmaxUnitsSt() - field->getBase(type)->getCounterUnits() < field->getBase(type)->getMaxUnits()) {
			i = field->getBase(type)->getmaxUnitsSt() - field->getBase(type)->getCounterUnits();
		}
		else {
			i = field->getBase(type)->getMaxUnits();
		}
		while (i != 0) {
			if (type == 'm') view = rand() % 2 + 1;		//1 or 2
			if (type == 'h') view = rand() % 2 + 3;		//3 or 4
			if (type == 'p') view = rand() % 2 + 5;		//5 или 6
			x = rand() % height;
			y = rand() % width;
			if (!field->addUnit(field->getBase(type)->createUnit(view), x, y)) {
				field->getBase(type)->setCounterUnits(field->getBase(type)->getCounterUnits() + 1); //counter++
				i--;
			}
		}
	}
	casePrintField();
}

void Gamer::caseAddCommand(int numberGamer) {
	int command, flag, i;
	cout << endl << name << ", вам необходимо добавить " << field->getMaxUnits() << " персонажей на поле. \n";
	cout << "Для этого вам необходимо ввести три числа:\n";
	cout << "Первое: номер команды добавления\n";

	if ((numberGamer == 1 && team1 == 'm') || (numberGamer == 2 && team2 == 'm')) {
		cout << "ВАМПИР: команда для добавления \"1\".\n";
		cout << "ОБОРОТЕНЬ: команда для добавления \"2\".\n";
	}
	else {
		cout << "ЦЕЛИТЕЛЬ: команда для добавления \"3\".\n";
		cout << "МАГ: команда для добавления \"4\".\n";
	}
	cout << "Два числа - координаты расположения героя (x; y).\n";
	if ((numberGamer == 1 && team1 == 'm') || (numberGamer == 2 && team2 == 'm')) cout << "Ваше поле левое.\n";
	else cout << "Ваше поле правое\n";

	command = dataCorrect(); 
	x = dataCorrect();
	y = dataCorrect();

	i = field->getMaxUnits();

	while (i != 0) {
		while (!caseError(command, numberGamer)) {
			cout << "Введите снова:\n";
			command = dataCorrect(); 
			x = dataCorrect(); 
			y = dataCorrect();
		}

		switch (command) {
		case 1:
			if (!field->addUnit(field->getBase('m')->createUnit(1), x, y)) {
				cout << "Создан Вампир\n";
				field->getBase('m')->setCounterUnits(field->getBase('m')->getCounterUnits() + 1); //counter++
				flag = 1;
			}
			else {
				if (field->addUnit(field->getBase('m')->createUnit(1), x, y) == 1) cout << "Позиция занята!\n";
				else cout << "Нельзя поставить на данный тип ландшафта!\n";
				cout << "Персонаж не создан! Введите снова!\n";
				i++;
				flag = 0;
			}
			break;

		case 2:
			if( !field->addUnit(field->getBase('m')->createUnit(2), x, y)){
				cout << "Создан Оборотень\n";
				field->getBase('m')->setCounterUnits(field->getBase('m')->getCounterUnits() + 1); //counter++
				flag = 1;
			}
			else {
				if (field->addUnit(field->getBase('m')->createUnit(2), x, y) == 1) cout << "Позиция занята!\n";
				else cout << "Нельзя поставить на данный тип ландшафта!\n";
				cout << "Персонаж не создан! Введите снова!\n";
				i++;
				flag = 0;
			}
			break;

		case 3:
			if(!field->addUnit(field->getBase('h')->createUnit(3), x, y)){
				cout << "Создан Целитель\n";
				field->getBase('h')->setCounterUnits(field->getBase('h')->getCounterUnits() + 1); //counter++
				flag = 1;
			}
			else {
				if (field->addUnit(field->getBase('h')->createUnit(3), x, y) == 1) cout << "Позиция занята!\n";
				else cout << "Нельзя поставить на данный тип ландшафта!\n";
				cout << "Персонаж не создан! Введите снова!\n";
				i++;
				flag = 0;
			}
			break;

		case 4:
			if(!field->addUnit(field->getBase('h')->createUnit(4), x, y)){
				cout << "Создан Маг\n";
				field->getBase('h')->setCounterUnits(field->getBase('h')->getCounterUnits() + 1); //counter++
				flag = 1;
			}
			else {
				if (field->addUnit(field->getBase('h')->createUnit(4), x, y) == 1) cout << "Позиция занята!\n";
				else cout << "Нельзя поставить на данный тип ландшафта!\n";
				cout << "Персонаж не создан! Введите снова!\n";
				i++;
				flag = 0;
			}
			break;
		}
		i--;
		if (flag) {
			casePrintField();

			cout << "Персонаж создан!\n";
			cout << "Осталось добавить " << i;
			if (i >= 5) cout << " юнитов\n";
			else cout << " юнита\n";

			if ((numberGamer == 1 && team1 == 'm') || (numberGamer == 2 && team2 == 'm')) {
				cout << "ВАМПИР: команда для добавления \"1\".\n";
				cout << "ОБОРОТЕНЬ: команда для добавления \"2\".\n";
			}
			else {
				cout << "ЦЕЛИТЕЛЬ: команда для добавления \"3\".\n";
				cout << "МАГ: команда для добавления \"4\".\n";
			}
		}

		if (i) {
			command = dataCorrect();
			x = dataCorrect();
			y = dataCorrect();
		}
	}
	casePrintField();

	if (numberGamer == 2) {
		cout << "Добавление нейтральных объектов\n";
		field->addNeutralObject();
		casePrintField();
	}
}

bool Gamer::caseError(int command, int numberGamer) {
	if ((numberGamer == 1 && team1 == 'm') || (numberGamer == 2 && team2 == 'm')) {
		if (command < 1 || command > 2) {
			cout << "Ошибка ведена неверная команда!\n";
			return 0;
		}
		if (y > (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь разместить юнитов на поле соперника!\n";
			return 0;
		}
	}
	else if ((numberGamer == 1 && team1 == 'h') || (numberGamer == 2 && team2 == 'h')) {
		if (command < 3 || command > 4) {
			cout << "Ошибка ведена неверная команда!\n";
			return 0;
		}
		if (y < (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь разместить юнитов на поле соперника!\n";
			return 0;
		}
	}
	if (x < 0 || y < 0) {
		cout << "Ошибка: введены отрицательные координаты!\n";
		return 0;
	}
	else if (x > field->getWidth() - 1 || y > field->getHeight() - 1) {
		cout << "Ошибка: координаты выходят из области поля!\n";
		return 0;
	}
	return 1;
}

void Gamer::caseDeleteUnit(int numberGamer) { //возможно и не нужна, но пока для примера удаления
	exit = 1;
	while (exit) {
		cout << "Введите координаты юнита, которого хотите удалить.\n";
		x = dataCorrect();
		y = dataCorrect();
		while (!caseError(numberGamer) || field->deleteUnit(x, y)) {
			if(field->deleteUnit(x, y)) cout << "На позиции нет юнита для удаления!\n";
			cout << "Введите снова:\n";
			x = dataCorrect();
			y = dataCorrect();
		}
		cout << "Юнит удален!\n";
		casePrintField();
		cout << "Введите 0, если хотите прекратить удаление.\n";
		cout << "Введите 1, если хотите продолжить удаление.\n";
		exit = dataCorrect();
	}
}

bool Gamer::caseError(int numberGamer) {

	if ((numberGamer == 1 && team1 == 'm') || (numberGamer == 2 && team2 == 'm')) {
		if (y > (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь удалить юнита соперника!\n";
			return 0;
		}
	}
	else if ((numberGamer == 1 && team1 == 'h') || (numberGamer == 2 && team2 == 'h')) {
		if (y < (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь удалить юнита соперника!\n";
			return 0;
		}
	}
	if (x < 0 || y < 0) {
		cout << "Ошибка: введены отрицательные координаты!\n";
		return 0;
	}
	else if (x > field->getWidth() - 1 || y > field->getHeight() - 1) {
		cout << "Ошибка: координаты выходят из области поля!\n";
		return 0;
	}
	return 1;
}

void Gamer::destination(char a, int steps) {
	switch (a) {
	case 'r':
		x2 = x;
		y2 = y + steps;
		break;
	case 'l':
		x2 = x;
		y2 = y - steps;
		break;
	case 'd':
		x2 = x + steps;
		y2 = y;
		break;
	case 'u':
		x2 = x - steps;
		y2 = y;
		break;
	case 'a':
		x2 = x - steps;
		y2 = y + steps;
		break;
	case 'b':
		x2 = x - steps;
		y2 = y - steps;
		break;
	case 'c':
		x2 = x + steps;
		y2 = y + steps;
		break;
	case 'f':
		x2 = x + steps;
		y2 = y - steps;
		break;
	}
}

int Gamer::checkUnit(int numberGamer) {
	if (field->getUnit(x, y) != nullptr) {
		if ((numberGamer == 1 && team1 == 'm') || (numberGamer == 2 && team2 == 'm')) {
			if (field->getUnit(x, y)->getView() != 1 && field->getUnit(x, y)->getView() != 2) {
				cout << "Вы пытайтесь переместить не своего юнита\n";
				return 1;
			}
			else {
				return 0;
			}
		}
		if ((numberGamer == 1 && team1 == 'h') || (numberGamer == 2 && team2 == 'h')) {
			if (field->getUnit(x, y)->getView() != 3 && field->getUnit(x, y)->getView() != 4) {
				cout << "Вы пытайтесь переместить не своего юнита\n";
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	else {
		cout << "На позиции нет юнита для перемещения\n";
		return 1;
	}
}

void Gamer::caseMovUnit(int numberGamer) {
	int steps, health, damage, armor, healthBaseBefore;
	char a;

	cout << "Для того, чтобы переместить юнита на другую позицию, необходимо ввести:\n\n";

	cout << "Текущие координаты расположения юнита (x, y);\n";
	cout << "Количество шагов (из допустимого).\n";
	cout << "Длина одного шага равна " << field->getStep() << endl;
	cout << "Допустимое количество шагов:\n Вампир : от 1 до 3.\n";
	cout << "Оборотень: от 1 до 2.\n Целитель: 1 шаг.\n Маг: от 1 до 2 шагов.\n\n";

	cout << "Направление движения юнитов:\n\n";									//пока все юниты ходят по всем направлениям
	cout << "\"l\" - влево; \"r\" - вправо; \"u\" - вверх; \"d\" - вниз\n";
	cout << "\"a\" - диагональ вверх-направо; \"b\" - диагональ вверх-налево;\n";
	cout << "\"c\" - диагональ вниз-направо; \"f\" - диагональ вниз-налево.\n";
	
	x = dataCorrect();
	y = dataCorrect();
	cin >> a;
	steps = dataCorrect();

	if (field->getUnit(x, y) != nullptr) {
		health = field->getUnit(x, y)->getHealth();
		damage = field->getUnit(x, y)->getDamage();
		armor = field->getUnit(x, y)->getArmor();
	}

	steps *= field->getStep();
	destination(a, steps);

	if (field->getBase(x2, y2) != nullptr) {
		healthBaseBefore = field->getBase(x2, y2)->getHealthBase();
	}

	while (checkUnit(numberGamer) || caseError(a, steps) || field->movingUnit(x, y, x2, y2, steps)) {

		if (field->movingUnit(x, y, x2, y2, steps) == 1) cout << "Невозможно выполнить перемещение на заданную позицию!\n";
		if (field->movingUnit(x, y, x2, y2, steps) == 2) cout << "Нельзя перемещаться на данный тип ландшафта\n";
		if (field->movingUnit(x, y, x2, y2, steps) == 3) cout << "На позиции нет юнита для перемещения\n";
		if (field->movingUnit(x, y, x2, y2, steps) == 4) cout << "Недопустимое количество шагов для данного юнита\n";

		cout << "Введите снова\n";
		x = dataCorrect();
		y = dataCorrect();
		cin >> a;
		steps = dataCorrect();

		if (field->getUnit(x, y) != nullptr) {
			health = field->getUnit(x, y)->getHealth();
			damage = field->getUnit(x, y)->getDamage();
			armor = field->getUnit(x, y)->getArmor();
		}
		steps *= field->getStep();										//в зависимости от размера поля - размер шага также изменяется - маштабируется
		destination(a, steps);

		if (field->getBase(x2, y2) != nullptr) {
			healthBaseBefore = field->getBase(x2, y2)->getHealthBase();
		}
	}
	casePrintField();
	if (field->getUnit(x2, y2) != nullptr) {
		if ((field->getUnit(x2, y2)->getHealth() - health) != 0) {
			cout << "Изменение здоровья на " << (field->getUnit(x2, y2)->getHealth() - health) << " единиц\n";
			cout << "Текущее здоровье " << field->getUnit(x2, y2)->getHealth() << " единиц\n";
		}
		else if ((field->getUnit(x2, y2)->getDamage() - damage) != 0) {
			cout << "Изменение урона на " << (field->getUnit(x2, y2)->getDamage() - damage) << " единиц\n";
			cout << "Текущий урон " << field->getUnit(x2, y2)->getDamage() << " единиц\n";
		}
		else if ((field->getUnit(x2, y2)->getArmor() - armor) != 0) {
			cout << "Изменение брони на " << (field->getUnit(x2, y2)->getArmor() - armor) << " единиц\n";
			cout << "Текущее состояние брони " << field->getUnit(x2, y2)->getArmor() << " единиц\n";
		}
	}

	if (field->getBase(x2, y2) != nullptr) {
		if (healthBaseBefore - field->getBase(x2, y2)->getHealthBase() != 0) { 
			cout << "Изменение здоровья базы на " << (healthBaseBefore - field->getBase(x2, y2)->getHealthBase()) << " единиц\n";
			cout << "Текущее здоровье базы " << field->getBase(x2, y2)->getHealthBase() << " единиц\n";
		}
	}
	
}

bool Gamer::caseError(char a, int steps) {
	if (x < 0 || y < 0 || x > field->getHeight() - 1 || y > field->getWidth() - 1) {
		cout << "Ошибка: данной позиции не существует!\n";
		return 1;
	}
	if (a == 'r' || a == 'l' || a == 'u' || a == 'd' || a == 'a' || a == 'b' || a == 'c' || a == 'f') {
	}
	else {
		cout << "Ошибка: команды не существует!\n";
		return 1;
	}
	if (steps < 0 || steps > 3) {
		cout << "Ошибка: недопустимое количество шагов!\n";
		return 1;
	}
	return 0;
}

void Gamer::casePrintField() {
	int k = 0;
	system("cls");
	system("color 85");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 143);

	cout << "  ";
	for (int i = 0; i < width; i++) {
		if (i < 10) cout << "  " << i << " ";
		else if (i == 10) cout << "  " << i << "  ";
		else cout << i << "  ";
	}
	cout << "\n" << "  -";
	for (int i = 0; i < width; i++) {
		cout << "----";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		if (k <= 9) cout << k++ << " ";
		else cout << k++;
		for (int j = 0; j < width; j++) {
			cout << "|";
			if (field->getUnit(i, j) == nullptr && field->getNeutralObject(i, j) == nullptr && field->getBase(i, j) == nullptr) {
				SetConsoleTextAttribute(hConsole, (field->getLandscape(i, j))->getColor());
				cout << "   ";
			}
			if (field->getUnit(i, j) != nullptr) {
				SetConsoleTextAttribute(hConsole, (field->getLandscape(i, j))->getNewColor(field->getUnit(i, j)->getView()));
				cout << " " << (field->getUnit(i, j))->getName() << " ";
			}
			if (field->getNeutralObject(i, j) != nullptr) {
				SetConsoleTextAttribute(hConsole, (field->getLandscape(i, j))->getNewColor(field->getNeutralObject(i, j)->getView()));
				cout << " " << (field->getNeutralObject(i, j))->getName() << " ";
			}
			if (field->getBase(i, j) != nullptr) {
				SetConsoleTextAttribute(hConsole, (field->getLandscape(i, j))->getNewColor(field->getBase(i, j)->getView()));
				cout << " " << (field->getBase(i, j))->getName() << " ";
			}
			SetConsoleTextAttribute(hConsole, 143);
			if (j == width - 1) cout << "|";
		}

		cout << "\n" << "  -";
		for (int i = 0; i < width; i++) {
			cout << "----";
		}
		cout << endl;
	}
	cout << endl;

	SetConsoleTextAttribute(hConsole, 79);
	cout << "   Счетчик юнитов:   \n";
	cout << ".....................\n";
	cout << ".People =        " << field->getBase('p')->getCounterUnits() << " .\n";
	cout << ".Monster =       " << field->getBase('m')->getCounterUnits() << "  .\n";
	cout << ".Hero =          " << field->getBase('h')->getCounterUnits() << "  .\n";
	cout << ".....................\n\n";
	SetConsoleTextAttribute(hConsole, 143);
}

void Gamer::infoUnit(int x, int y) { //создать подобное для нейтральных?	
	if (field->getUnit(x, y) != nullptr) {
		cout << "Здоровье: " << field->getUnit(x, y)->getHealth() << " единиц.\n";
	    cout << "Урон: " << field->getUnit(x, y)->getDamage() << " единиц.\n";
		cout << "Броня: " << field->getUnit(x, y)->getArmor() << " единиц.\n";
	}
	else {
		cout << "На данной позиции нет юнита\n";
	}

}

void Gamer::infoBase() {
	char a;
	int flag = 0;
	cout << "Введите m, h или p, если хотите увидеть информацию о базе монстров, героев или людей соответственно\n";
	do {
		cin >> a;
		switch (a) {
		case 'm':
			cout << "База монстров\n";
			
			break;
		case 'h':
			cout << "База героев\n";
			break;
		case 'p':
			cout << "База людей\n";
			break;
		default:
			cout << "Введен неверный символ. Попробуйте снова\n";
			flag = 1;
		} 
	}while (flag == 1);
	
	cout << "Здоровье: " << field->getBase(a)->getHealthBase() << " единиц.\n";
	cout << "Максимальное количество юнитов, относящихся к одной базе " << field->getBase(a)->getmaxUnitsSt() << " единиц.\n";
	cout << "Максимальное количество юнитов, создаваемое во время игры " << field->getBase(a)->getMaxUnits() << " единиц.\n";
}

void Gamer::saveField() {
	GameField copy(*field);
	//copy.printCurField();
	/*GameField a(10, 10); //проверка оператора =
	GameField b(20, 20);
	a = b;*/
	
	cout << "Игровое поле сохранено.\n";
}

string Gamer::getName() {
	return name;
}

int Gamer::theEnd() {
	return field->getBase('p')->getCounterUnits();
}
