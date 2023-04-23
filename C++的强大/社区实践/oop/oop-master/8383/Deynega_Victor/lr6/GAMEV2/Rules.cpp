#include "Rules.h"
#include <conio.h>
#include "FieldBlock.h"


Rules::Rules() {
	key = 0;
	checker = nullptr;
	board = nullptr;
	attackBase = nullptr;
	proxyField = nullptr;
}

Rule1::Rule1() {
	key = 0;
	board = new GameField();
	menuFlag = false;
	TypeChecker* checker = new ArcherCheck;
	checker->setNext(new BallistaCheck())->setNext(new AtFarmCheck())->setNext(new BomberCheck())->setNext(new BomberGeneralCheck())
		->setNext(new AssasinCheck())->setNext(new BufferCheck())->setNext(new WallCheck())->setNext(new ImmWallCheck())->setNext(new HealTowCheck())
		->setNext(new HealUnCheck())->setNext(new PudgeCheck())->setNext(new ComanderCheck());
	board = new GameField();
	attackBase = new Base(20); //defolt size = 20
	//board.bx = attackBase->x;
	//board.by = attackBase->y;
	proxyField = new Proxy(board);
	logger.switchLogStream("file");
	logger.turnOnOffLog("off");
}

int Rule1::whoLose() { //1 - attack lose; 2 - defence lose
	if (attackBase->numOfUnits <= 0) return 1;
	//if(defBase->health <= 0 ) return 2;
}

void  Rules::menu() {
	std::cout << "Press s to save game.\n";
	std::cout << "Press d to download game.\n";
	std::cout << "Press n to start new game.\n";
}


void Rules::unitAttackInfo() {
	std::cout << "Cell is clear you can spawn:\n";
	std::cout << "Press 1 to spawn archer\n";
	std::cout << "Press 2 to spawn ballista\n";
	std::cout << "Press 5 to spawn bomber\n";
	std::cout << "Press 6 to spawn general-bomber\n";
	std::cout << "Press 7 to spawn assasin\n";
	std::cout << "Press 8 to spawn buffer\n";
	std::cout << "Press 0 to end turn\n";
}


int Rule1::action(int turnCounter) { //1 - new game
	//even = attack turn, odd = def
	key = _getch();
	if (key == 27) { //press esc
		menu();
		key = _getch();
		if (key == 115) { //key 's'
			//add save
			return 0;
		}
		if (key == 100) { //key = 'd'
			//add download memento
			return 0;
		}
		if (key == 110) { //key  = 'n'
			return 1;
		}
	}
	else {
		int cellX, cellY;
		std::cout << "\nType x and y of chosen cell\n";
		std::cin >> cellX;
		std::cin >> cellY;
		//
		FieldBlock* fieldPtr = board->field;
		if (proxyField->proxyIsLansdscape(cellX, cellY)) { //if can't smth bcos of landscape
			if (fieldPtr[cellY * (board->size) + cellX].landType->getType() == 2) {
				std::cout << "There is lake!\n";
				system("pause");
				return 0;
			}
			if ((fieldPtr[cellY * board->size + cellX].landType->getType() == 1)){
				std::cout << "There is mountain!\n";
				system("pause");
				return 0;
			}
		}
		if (proxyField->proxyChecker(cellX, cellY)) { //if landscape is ok and no units here
			int type;
			unitAttackInfo();
			std::cin >> type;
			checker->spawnSmth(type, *attackBase, *board, cellX, cellY);
			//logger.printResUnit(board.field[x + y * size].unit);
			return 0;
		}
		int ut = fieldPtr[cellY * (board->size) + cellX].getUnitType();
		std::cout << "You can relocate " << fieldPtr[cellY * (board->size) + cellX].unit->getName() << "\n";
		std::cout << "Type x and y:\n";
		int relocX, relocY;
		std::cin >> relocX >> relocY;
		fieldPtr[cellY * board->size + cellX].unit->relocate(relocX, relocY, *board, board->size);
		std::cout << "You also can attack smth.\n";
		int targX, targY;
		std::cout << "Type coordinats of target:\n";
		std::cin >> targX >> targY;
		if ((ut == 1 || ut == 2) && turnCounter%2 == 0 ) { //if archer/ballista
			if (!dynamic_cast<Archer*>(fieldPtr[cellY * board->size + cellX].unit)->makeShot(targX, targY, *board, fieldPtr[cellY * board->size + cellX].unit->damage)){
				std::cout << "There is no units here!\n";
			}
			else {
				std::cout << "Success shot!\n";
			}
			return 0;
		}
		if ((ut == 13) && turnCounter % 2 == 1) { //if pudge
			dynamic_cast<Pudge*>(fieldPtr[cellY * board->size + cellX].unit)->hook(targX, targY, *board);
			return 0;
		}
		if ((ut == 14) && turnCounter % 2 == 1) { //if comander
			dynamic_cast<Comander*>(fieldPtr[cellY * board->size + cellX].unit)->poising(targX, targY, *board);
			return 0;
		}
	}

}



Rule2::Rule2() { //spawn max units mode
	key = 0;
	board = new GameField();
	menuFlag = false;
	TypeChecker* checker = new ArcherCheck;
	checker->setNext(new BallistaCheck())->setNext(new AtFarmCheck())->setNext(new BomberCheck())->setNext(new BomberGeneralCheck())
		->setNext(new AssasinCheck())->setNext(new BufferCheck())->setNext(new WallCheck())->setNext(new ImmWallCheck())->setNext(new HealTowCheck())
		->setNext(new HealUnCheck())->setNext(new PudgeCheck())->setNext(new ComanderCheck());
	attackBase = new Base(20); //defolt size = 20
	//board.bx = attackBase->x;
	//board.by = attackBase->y;
	proxyField = new Proxy(board);
	logger.switchLogStream("file");
	logger.turnOnOffLog("off");
}


int Rule2::whoLose() { //1 - attack lose; 2 - defence lose
	if (attackBase->numOfUnits == attackBase->maxUnits / 2) return 2;
}



int Rule2::action(int turnCounter) { //1 - new game
	key = _getch();
	if (key == 27) { //press esc
		menu();
		key = _getch();
		if (key == 115) { //key 's'
			//add save
			return 0;
		}
		if (key == 100) { //key = 'd'
			//add download memento
			return 0;
		}
		if (key == 110) { //key  = 'n'
			return 1;
		}
	}
	else {
		int cellX, cellY;
		std::cout << "\nType x and y of chosen cell\n";
		std::cin >> cellX;
		std::cin >> cellY;
		//
		FieldBlock* fieldPtr = board->field;
		if (proxyField->proxyIsLansdscape(cellX, cellY)) { //if can't smth bcos of landscape
			if (fieldPtr[cellY * (board->size) + cellX].landType->getType() == 2) {
				std::cout << "There is lake!\n";
				system("pause");
				return 0;
			}
			if ((fieldPtr[cellY * board->size + cellX].landType->getType() == 1)) {
				std::cout << "There is mountain!\n";
				system("pause");
				return 0;
			}
		}
		if (proxyField->proxyChecker(cellX, cellY)) { //if landscape is ok and no units here
			int type;
			unitAttackInfo();
			std::cin >> type;
			checker->spawnSmth(type, *attackBase, *board, cellX, cellY);
			//logger.printResUnit(board.field[x + y * size].unit);
			return 0;
		}
		int ut = fieldPtr[cellY * (board->size) + cellX].getUnitType();
		std::cout << "You can relocate " << fieldPtr[cellY * (board->size) + cellX].unit->getName() << "\n";
		std::cout << "Type x and y:\n";
		int relocX, relocY;
		std::cin >> relocX >> relocY;
		fieldPtr[cellY * board->size + cellX].unit->relocate(relocX, relocY, *board, board->size);
		std::cout << "You also can attack smth.\n";
		int targX, targY;
		std::cout << "Type coordinats of target:\n";
		std::cin >> targX >> targY;
		if (ut == 1 || ut == 2) { //if archer/ballista
			if (!dynamic_cast<Archer*>(fieldPtr[cellY * board->size + cellX].unit)->makeShot(targX, targY, *board, fieldPtr[cellY * board->size + cellX].unit->damage)) {
				std::cout << "There is no units here!\n";
			}
			else {
				std::cout << "Success shot!\n";
			}
			return 0;
		}
	}

}