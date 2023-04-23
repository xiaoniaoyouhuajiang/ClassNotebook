#include "Facade.h"

Facade::Facade(Gamer* gamer) : pointer(gamer), idGamer(0), task('0'), choice('0'), mode(0) {
	UF = new UnitFunct();
	UF->setPointer(pointer);
	BF = new BaseFunct();
	BF->setPointer(pointer);
}

void Facade::setTask(char task) {
	this->task = task;
	if (task == 'u') listOptionUnit();
	else listOptionBase();
}

void Facade::editMode(int mode, int idGamer) {
	this->mode = mode;
	this->idGamer = idGamer;
}

void Facade::checkListUnit() {
	int error = 1;
	while (error) {
		cin >> choice;
		switch (choice) {
		case 'h':
			error = 0;
			break;
		case 'm':
			error = 0;
			break;
		case 'i':
			if (!mode) error = 0;
			std::cout << "Команда не доступна\n";
			break;
		case 'c':
			if (!mode) error = 0;
			std::cout << "Команда не доступна\n";
			break;
		default:
			std::cout << "Команды не существует - попробуйте еще раз\n";
			break;
		}
	}
}

void Facade::listOptionUnit() {
	std::cout << "Функции для работы с юнитами:\n";

	if (!mode) {
		std::cout << "Режим настроек\n";
		std::cout << "0) Помощь - нажмите символ \'h\'.\n";
		std::cout << "1) Переместить юнита на другую позицию ( - нажмите символ \'m\'.\n";
		std::cout << "2) Вывести информацию о юните - нажмите символ \'i\'.\n";
		std::cout << "3) Поменять местами своих юнитов - нажмите символ  \'c\'.\n";
	}
	else {
		std::cout << "Режим игры\n";
		std::cout << "1) Переместить юнита на другую позицию (+атака) - нажмите символ \'m\'.\n";
	}
	checkListUnit();
	shablonCommandUnit();
}

void Facade::readerCommands() {
	command.push_back(choice);
	command.push_back(idGamer + '0');
	std::vector <char> temp;

	temp.resize(20);
	for (int i = 0; i < temp.size(); i++) {
		cin >> temp[i];
		if (temp[i] == '.') break;
		if (temp[i] != ',') command.push_back(temp[i]);
	}
	command.push_back(mode + '0');
	temp.clear();
}

void Facade::shablonCommandUnit() {
	std::cout << "Пожалуйста, строго следуйте формату.\n";

	if (choice == 'h') {
		std::cout << "Формат команды: отсутствует.\n";
		UF->help();
	}
	else {
		if (choice == 'm') {
			std::cout << "Формат команды: x, y, направление, количество шагов.\n";
		}
		else if (choice == 'i') {
			std::cout << "Формат команды: x, y.\n";
		}
		else if (choice == 'c') {
			std::cout << "Формат команды: x1, y1, x2, y2.\n";
		}
		readerCommands();
		UF->setParam(command);
		command.clear();
	}
}

void Facade::checkListBase() {
	int error = 1;
	while (error) {
		cin >> choice;
		switch (choice) {
		case 'm':
			if (!mode) error = 0;
			else std::cout << "Команда не доступна\n";
			break;
		case 'g':
			if (!mode) error = 0;
			else std::cout << "Команда не доступна\n";
			break;
		case 'p':
			if (!mode) error = 0;
			else std::cout << "Команда не доступна\n";
			break;
		case 'r':
			if (mode) error = 0;
			else std::cout << "Команда не доступна\n";
			break;
		case 'a':
			if (mode) error = 0;
			else std::cout << "Команда не доступна\n";
			break;
		default:
			std::cout << "Команды не существует - попробуйте еще раз\n";
			break;
		}
	}
}


void Facade::listOptionBase() {
	if (!mode) {
		std::cout << "Функции для просмотра базы:\n";
		std::cout << "1) Вывести информацию о базе Монстров ( - нажмите символ \'m\'.\n";
		std::cout << "2) Вывести информацию о базе Героев ( - нажмите символ \'g\'.\n";
		std::cout << "3) Вывести информацию о базе Людей ( - нажмите символ \'p\'.\n";
	}
	else if (mode) {
		std::cout << "Функции для взаимодействия с базой:\n";
		std::cout << "1) Восстановить состояние базы - нажмите символ \'r\'.\n";
		std::cout << "2) Напасть на базу - нажмите символ \'a\'.\n";
		std::cout << "Для атаки на базу юнит должен находится в зоне ее досягаемости\n";
	}
	checkListBase();
	shablonCommandBase();
}

void Facade::shablonCommandBase() {
	std::cout << "Пожалуйста, строго следуйте формату.\n";
	if (choice == 'm' || choice == 'g' || choice == 'p') {
		command.push_back(choice);
		command.push_back(idGamer + '0');
	}
	else if (choice == 'a') {
		std::cout << "Формат команды: x, y, направление, количество шагов до базы.\n";
		readerCommands();
	}
	else if (choice == 'r') {
		std::cout << "Формат команды: x, y - коорд. юнита, x2, y2 - коорд. базы\n";
		readerCommands();
	}
	BF->setParam(command);
	command.clear();
}

Facade::~Facade(){
	delete UF;
	delete BF;
}

void Facade::design() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 112);

	cout << "\n\t\t    Обозначения на игровом поле:                      \n";
	cout << "......................................................................\n";
	cout << ".\t                     ЮНИТЫ:                                  .\n";
	SetConsoleTextAttribute(hConsole, 116);
	cout << ". ВАМПИР:    " << (char)2 << " тип монстр\t\t\t\t\t     .\n";
	cout << ". ОБОРОТЕНЬ: " << (char)4 << " тип монстр\t\t\t\t\t     .\n";
	SetConsoleTextAttribute(hConsole, 113);
	cout << ". ЦЕЛИТЕЛЬ:  " << (char)3 << " тип герой\t\t\t\t\t     .\n";
	cout << ". МАГ:       " << (char)15 << " тип герой\t\t\t\t\t     .\n";
	SetConsoleTextAttribute(hConsole, 112);
	cout << ". ЧЕЛОВЕК:   " << (char)1 << " тип человек\t\t\t\t\t     .\n";
	cout << ". ОХОТНИК:   " << (char)6 << " тип человек\t\t\t\t\t     .\n";

	cout << "......................................................................\n";
	cout << ".\t               НЕЙТРАЛЬНЫЕ ОБЪЕКТЫ:                          .\n";
	cout << ". СВЯТОЙ КРЕСТ:    " << (char)390 << " Св-во: - здоровье у вампиров и магов            .\n";
	cout << ". ЗМЕЯ:            " << (char)382 << " Св-во: - здоровье у всех, кроме вампиров и магов.\n";
	cout << ". ТАБЛЕТКА:        " << (char)299 << " Св-во: + здоровье любому юниту                  .\n";
	cout << ". КОРОБКА-СЮРПРИЗ: " << (char)63 << " Св-во: + здоровье или урон любому юниту         .\n";

	cout << "......................................................................\n";
	cout << ".\t                   ЛАНДШАФТ:                                 .\n";
	cout << ".";
	SetConsoleTextAttribute(hConsole, 111);
	cout << "  ";
	SetConsoleTextAttribute(hConsole, 47);
	cout << "  ";
	SetConsoleTextAttribute(hConsole, 112);
	cout << " - трава. Может наступать любой юнит.\t\t\t     .\n";

	cout << ".";
	SetConsoleTextAttribute(hConsole, 191);
	cout << "  ";
	SetConsoleTextAttribute(hConsole, 112);
	cout << " - озеро. Нельзя наступать никому кроме целителя.\t\t     .\n";

	cout << ".";
	SetConsoleTextAttribute(hConsole, 79);
	cout << "  ";
	SetConsoleTextAttribute(hConsole, 112);
	cout << " - ритуальный круг. Можно наступать только магам.\t\t     .\n";

	cout << ".";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "  ";
	SetConsoleTextAttribute(hConsole, 112);
	cout << " - яма. Никому нельзя наступать.\t\t\t\t     .\n";
	cout << "......................................................................\n";
	cout << ".\t                     БАЗЫ:                                   .\n";
	SetConsoleTextAttribute(hConsole, 112);
	cout << "." << (char)203;
	cout << " - база людей\t\t\t\t\t\t\t     .\n";
	SetConsoleTextAttribute(hConsole, 116);
	cout << "." << (char)204;
	cout << " - база монстров\t\t\t\t\t\t     .\n";
	SetConsoleTextAttribute(hConsole, 113);
	cout << "." << (char)195;
	cout << " - база героев\t\t\t\t\t\t     .\n";
	cout << "......................................................................\n\n";
	SetConsoleTextAttribute(hConsole, 143);
}