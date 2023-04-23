#include "Control.h"


Control::Control() {
	gamer = new Gamer;
	counter = 0;
}

void Control::BeginGame() {
	char change;
	int x, y;

	gamer->caseField(); // 1 раз

	while (counter != 2) {
		counter++;
		gamer->caseName(counter);
		info();
		gamer->caseAddCommand(counter);
		info();
		change = 'n';

		while (change == 'n') {
			cout << "\nЕсли вы ошиблись и хотите переместить юнитов нажмите \'m\'\n";
			cout << "Если вы хотите сохранить текущее состояние игры нажмите \'s\'\n";
			cout << "Если вы хотите узнать текущее состояние юнита нажмите \'i\'\n";
			cout << "Если вы хотите узнать текущее состояние базы нажмите \'b\'\n";
			cout << "Для выхода из режима настроек нажмите \'e\'\n\n";
			
			cin >> change;
			switch (change) {
			case 'm':
				gamer->caseMovUnit(counter);
				change = 'n';
				break;
			case 's':
				gamer->saveField();
				change = 'n';
				break;
			case 'i':
				cout << "Введите координаты юнита\n";
				cin >> x >> y;
				gamer->infoUnit(x, y);
				change = 'n';
				break;
			case 'b':
				gamer->infoBase();
				change = 'n';
				break;
			case 'd':
				gamer->caseDeleteUnit(counter);
				change = 'n';
				break;
			default:
				break;
			}
		}
		if (counter == 1) system("cls");

	}
	GameStart();
}

void Control::GameStart() {
	int k, j = 0;
	counter = 1;

	while (gamer->theEnd() != 0) { //людей не осталось
		cout << "\nХод игрока №" << counter << " \n\n";
		for (int i = 0; i < 5; i++) {
			k = 5 - i;
			if (k == 5) cout << "Вы можете сделать " << 5 - i << " ходов\n";
			else if (k == 1) cout << "Вы можете сделать " << 5 - i << " ход\n";
			else cout << "Вы можете сделать " << 5 - i << " ходa\n";
			gamer->caseMovUnit(counter);
		}
		if (counter == 1) counter++;
		else counter--;
		j++;
		if (j % 4 == 0) { //пополнение юнитов через каждый 2 хода у каждого игрока 
			gamer->addUnitRandom('m');
			gamer->addUnitRandom('h');
		}
		if (j % 6 == 0) {
			gamer->addUnitRandom('p');
		}
	}
	cout << "Игра окончена!\n";
}

void Control::info() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 112);

	cout << "\n\t\t    Обозначения на игровом поле:                      \n";
	cout << "......................................................................\n";
	cout << ".\t                     ЮНИТЫ:                                  .\n";
	cout << ". ВАМПИР:    " << (char)2 << " тип монстр\t\t\t\t\t     .\n";
	cout << ". ОБОРОТЕНЬ: " << (char)4 << " тип монстр\t\t\t\t\t     .\n";
	cout << ". ЦЕЛИТЕЛЬ:  " << (char)3 << " тип герой\t\t\t\t\t     .\n";
	cout << ". МАГ:       " << (char)15 << " тип герой\t\t\t\t\t     .\n";
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
	cout << "." << (char)203;
	cout << " - база людей\t\t\t\t\t\t\t     .\n";
	cout << "." << (char)204;
	cout << " - база монстров\t\t\t\t\t\t     .\n";
	cout << "." << (char)195;
	cout << " - база героев\t\t\t\t\t\t     .\n";
	cout << "......................................................................\n\n";
	SetConsoleTextAttribute(hConsole, 143);
}