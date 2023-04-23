#include "UInt.h" //check
#include "GameField.h"
#include "FieldBlock.h" //
#include "Units.h" //
#include "Base.h"
#include "Factory.h" //
#include "Landscape.h" //
#include "Neutral.h"
#include "NeutralFactory.h"
#include "chainOfResponsibility.h"
#include "Adapter.h"

#include "File.h"


#include <iostream>
#include <iomanip>
#include <vector>

void Uint::veryBadDecision() {
	Adapter logger;
	logger.switchLogStream("file");
	logger.turnOnOffLog("on");
	TypeChecker* checker = new ArcherCheck;
	checker->setNext(new BallistaCheck())->setNext(new AtFarmCheck())->setNext(new BomberCheck())->setNext(new BomberGeneralCheck());
	PosionFactory posion;
	DoubleFactory doubl;
	KnivesFactory knife;
	ArrowFactory arrow;
	Objector objector;
	Unit tempUnit;
	int x, y, oldX, oldY, bc;
	int type = 0;
	int size = 0;
	int chose;
	int turnCounter = 0;
	std::vector<NeutralObject*> objects;
	std::cout << "type N:\n";
	std::cin >> size;
	size = 7;
	GameField board(size); //command mb
	//board.draw();
	Proxy proxyObj(&board);
	objects.push_back(posion.createObject(0, 1)); //temp
	board.field[board.size].neutralPtr = objects[0]; 
	objects.push_back(doubl.createObject(3, 2));
	board.field[2 * board.size + 3].neutralPtr = objects[1];
	objects.push_back(knife.createObject(2, 2));
	board.field[2 * board.size + 2].neutralPtr = objects[2];
	objects.push_back(arrow.createObject(6, 3));
	board.field[3 * board.size + 6].neutralPtr = objects[3];

	std::cout << "Type coords of base: \n";
	std::cin >> x >> y;
	if (!((y == 0) && (x > -1) && (x < 7))) {
		y = 0;
		x = 3;
	}
	board.bx = x;
	board.by = y;
	Base attackBase(board.size, board, x, y);

	logger.printBase(&attackBase); //logg
	board.draw();

	std::vector<int> param;
	//std::string ooo;
	//File newOne("memento.txt", true);
	//std::cout << newOne.read(ooo);
	//exit(0);
	while (turnCounter < 4) { // temp
		std::cout << "\nNEW TURN!\n";
		turnCounter++;
		for (int i = 0; i < 1; i++) {
			std::cout << "\nType x of chosen cell\n";
			std::cout << "Type y of choosen cell\n";
			std::cin >> x;
			std::cin >> y;
			if (x == 0 && y == 0) {
				board.loadMemento(param);
				continue;
			}
			if (proxyObj.proxyIsLansdscape(x, y)) { //if can't smth bcos of landscape
				if (board.field[y * size + x].landType->getType() == 2) {
					std::cout << "There is lake!\n";
					system("pause");
					continue;
				}
				if (board.field[y * size + x].landType->getType() == 1) {
					std::cout << "There is mountain!\n";
					system("pause");
					continue;
				}
			}
			if(proxyObj.proxyChecker(x, y)){ //if landscape is ok and no units here
				printInfo();
				std::cin >> type;
				checker->spawnSmth(type, attackBase, board, x, y);
				logger.printResUnit(board.field[x + y * size].unit); //logg
				board.createMemento(attackBase.health, turnCounter, attackBase.numOfUnits);
				/*if (board.field[y * size + x].unit == nullptr) {
					std::cout << "AAAAAAAAAAAA";
				}
				int Aa = board.field[y * size + x].unit->type;
				std::cout << Aa;
				*/
			}
			else { //if user pick smth
				if (y == board.by && x == board.bx) { //base action  :-( 
					std::cout << "You pick base, you can check how many units you can place - 1\nYou can check how many hp left - 2\n";
					std::cin >> bc;
					if (bc == 1) {
						attackBase.enableSpots();
						system("pause");
					}
					else {
						if (bc == 2) {
							attackBase.baseHealth();
							system("pause");
						}
						else {
							std::cout << "Cya next turn:)\n";
						}
					}
					continue;
				}
				switch (board.field[y * size + x].unit->type) {
				case 1:{
					std::cout << "You pick archer! You can relocate it or make shot.\n 1 - shot; 2 - relocate:\nType x and y:\n";
					oldX = x;
					oldY = y;
					std::cin >> chose;
					if (chose == 1) {
						std::cout << "Type coordinats of target:\n";
						std::cin >> x >> y;
						if (!dynamic_cast<Archer*>(board.field[oldY * size + oldX].unit)->makeShot(x, y, board, board.field[oldY * size + oldX].unit->damage)) {
							std::cout << "There is no units here!\n";
						}
						else {
							std::cout << "Shot made successfully!\nHealth of uint is: ";
							std::cout << board.field[y * size + x].unit->health << "\n";
							logger.printAttack(board.field[oldY * size + oldX].unit, board.field[y * size + x].unit); //logg
							if (board.field[y * size + x].unit->health <= 0) {
								logger.printDeathUnit(board.field[y * size + x].unit); //logg
								attackBase.deleteUnit(x, y, board);
							}
						}
						system("pause");
					}

					std::cout << "Press 2 to relocate, 0 to end turn\n";
					std::cin >> chose;
					if (chose == 2) {
						std::cout << "Type x and y:\n";
						std::cin >> x >> y;
						if (!proxyObj.proxyChecker(x, y)) {
							std::cout << "You can't move archer to this point(((\n";
							system("pause");
							attackBase.deleteUnit(oldX, oldY, board);
							break;
						}
						if (board.field[y * size + x].neutralPtr != NULL) {
							objector.p = board.field[y * size + x].neutralPtr;
							objector + *board.field[oldY * size + oldX].unit;
							board.field[y * size + x].neutralPtr = NULL;
							system("pause");
						}
						if (board.field[oldY * size + oldX].unit->relocate(x, y, board, size)) {
							logger.printMove(board.field[y * size + x].unit, oldX, oldY);
							std::cout << "Archer move successfully!\n";
						}
						else {
							std::cout << "You can't move archer to this point(((\n";
							system("pause");
						}
					}
					break;
				}
				case 2: {
					oldX = x;
					oldY = y;
					std::cout << "You pick ballista! You can relocate it or make shot.\n 1 - shot; 2 - relocate:\nType x and y:\n";
					std::cin >> chose;
					if (chose == 1) {
						std::cout << "Type coordinats of target:\n";
						std::cin >> x >> y;
						if (!dynamic_cast<Ballista*>(board.field[oldY * size + oldX].unit)->makeShot(x, y, board, board.field[oldY * size + oldX].unit->damage)) {
							std::cout << "There is no units here!\n";
						}
						else {
							std::cout << "Shot made successfully!\nHealth of uint is: ";
							std::cout << board.field[y * size + x].unit->health << "\n";
							if (board.field[y * size + x].unit->health <= 0) {
								attackBase.deleteUnit(x, y, board);
							}
						}
						
						system("pause");
					}
					std::cout << "Press 2 to relocate, 0 to end turn\n";
					std::cin >> chose;
					if (chose == 2) {
						std::cout << "Type x and y:\n";
						std::cin >> x >> y;
						if (!proxyObj.proxyChecker(x, y)) {
							std::cout << "You can't move ballista to this point(((\n";
							system("pause");
							attackBase.deleteUnit(oldX, oldY, board);
							break;
						}
						if (board.field[y * size + x].neutralPtr != NULL) {
							objector.p = board.field[y * size + x].neutralPtr;
							objector + *board.field[oldY * size + oldX].unit;
							board.field[y * size + x].neutralPtr = NULL;
							system("pause");
						}
						if (board.field[oldY * size + oldX].unit->relocate(x, y, board, size)) {
							std::cout << "Ballista moved successfully!\n";
							logger.printMove(board.field[y * size + x].unit, oldX, oldY);
						}
						else {
							std::cout << "You can't move ballista to this point(((\n";
							system("pause");
						}
					}
					break;
				}
				case 3: {
					std::cout << "You pick farm tower! You can relocate it.\nType x and y:\n";
					oldX = x;
					oldY = y;
					std::cin >> x >> y;
					if (!proxyObj.proxyChecker(x, y)) {
						std::cout << "You can't move tower to this point(((\n";
						attackBase.deleteUnit(oldX, oldY, board);
						system("pause");
						break;
					}
					if (board.field[y * size + x].neutralPtr != NULL) {
						objector.p = board.field[y * size + x].neutralPtr;
						objector + *board.field[oldY * size + oldX].unit;
						board.field[y * size + x].neutralPtr = NULL;
						system("pause");
					}
					if (board.field[oldY * size + oldX].unit->relocate(x, y, board, size)) {
						logger.printMove(board.field[y * size + x].unit, oldX, oldY);
						std::cout << "Farm tower move successfully!\n";
					}
					else {
						std::cout << "You can't move farm tower to this point(((\n";
						system("pause");
						
					}
					break;
				}
				case 5: {
					std::cout << "You pick bomber, it moves automaticaly\n";
					system("pause");
					break;
				}
				case 6: {
					std::cout << "You pick general, it moves automaticaly\n";
					system("pause");
					break;
				}
				}
			}
		}
		for (int i = size - 1; i >= 0; i--) {
			for (int j = size - 1; j >= 0; j--) {
				if ((board.field[i * size + j].getUnitType() == 5) || (board.field[i * size + j].getUnitType() == 6)) {
					board.field[i * size + j].unit->relocate(j, i + 1, board, size);
					if (board.field[(i+1) * size + j].neutralPtr != NULL) {
						objector.p = board.field[(i+1) * size + j].neutralPtr;
						objector + *board.field[(i + 1) * size + j].unit;
						board.field[(i + 1) * size + j].neutralPtr = NULL;
						system("pause");
					}
				}
			}
		}
		system("cls");
		board.draw();
	}
}



void Uint::printInfo() {
	std::cout << "Cell is clear you can spawn:\n";
	std::cout << "Press 1 to spawn archer\n";
	std::cout << "Press 2 to spawn ballista\n";
	std::cout << "Press 3 to spawn farm tower\n";
	std::cout << "Press 5 to spawn bomber\n";
	std::cout << "Press 6 to spawn general-bomber\n";
	std::cout << "Press 0 to end turn\n";
}
