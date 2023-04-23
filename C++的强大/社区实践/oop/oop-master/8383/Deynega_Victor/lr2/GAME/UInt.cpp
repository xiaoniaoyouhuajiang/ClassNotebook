#include "UInt.h"
#include "GameField.h"
#include "FieldBlock.h" //
#include "Units.h" //
#include "Base.h"
#include "Factory.h" //
#include "Landscape.h" //
#include "Neutral.h"
#include "NeutralFactory.h"

#include <iostream>
#include <iomanip>
#include <vector>

void Uint::veryBadDecision() {
	PosionFactory posion;
	DoubleFactory doubl;
	KnivesFactory knife;
	ArrowFactory arrow;
	Objector objector;
	Unit tempUnit;
	int x, y, oldX, oldY;
	int type = 0;
	int size = 0;
	int chose;
	int turnCounter = 0;
	std::vector<NeutralObject*> objects;
	std::cout << "type N:\n";
	std::cin >> size;
	size = 7;
	GameField board(size);
	Proxy proxyObj(&board);
	objects.push_back(posion.createObject(0, 1)); //temp
	board.field[board.size].neutralPtr = objects[0]; 
	objects.push_back(doubl.createObject(3, 2));
	board.field[2 * board.size + 3].neutralPtr = objects[1];
	objects.push_back(knife.createObject(2, 2));
	board.field[2 * board.size + 2].neutralPtr = objects[2];
	objects.push_back(arrow.createObject(6, 3));
	board.field[3 * board.size + 6].neutralPtr = objects[3];


	Base attackBase(board.size, board);
	board.draw();
	while (turnCounter < 4) { // temp
		std::cout << "\nNEW TURN!\n";
		turnCounter++;
		for (int i = 0; i < 1; i++) {
			std::cout << "\nType x of chosen cell\n";
			std::cout << "Type y of choosen cell\n";
			std::cin >> x;
			std::cin >> y;
		//	if (board.field[y * size + x].isEmpty) {
			if(proxyObj.proxyChecker(x, y)){
				std::cout << "Cell is clear you can spawn:\n";
				std::cout << "Press 1 to spawn archer\n";
				std::cout << "Press 2 to spawn ballista\n";
				std::cout << "Press 3 to spawn farm tower\n";
				std::cout << "Press 5 to spawn bomber\n";
				std::cout << "Press 6 to spawn general-bomber\n";
				std::cout << "Press 0 to end turn\n";
				std::cin >> type;
				switch (type) {
				case 1: {
					attackBase.unitArr.push_back(attackBase.createArcher(x, y));
					board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
					board.putUnitOn(x, y, 1, attackBase.unitArr.size() - 1, board);
				//	board.field[y * size + x].unitType = 1;
				//	board.numOfEmptyBlocks--;
					attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1; //put on factory later
				//	board.field[y * size + x].isEmpty = false;
				//	board.field[y * size + x].unitIndex = cont.unitArr.size() - 1;
					break;
				}
				case 2: {
					attackBase.unitArr.push_back(attackBase.createBallista(x, y));
					board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
					board.putUnitOn(x, y, 2, attackBase.unitArr.size() - 1, board);
					attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
					break;
				}
				case 3: {
					attackBase.unitArr.push_back(attackBase.createAtFarm(x, y));
					board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
					board.putUnitOn(x, y, 3, attackBase.unitArr.size() - 1, board);
					attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
					break;
				}
				case 5: {
					attackBase.unitArr.push_back(attackBase.createBomber(x, y));
					board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
					board.putUnitOn(x, y, 5, attackBase.unitArr.size() - 1, board);
					attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
					break;
				}

				case 6: {
					attackBase.unitArr.push_back(attackBase.createGeneral(x, y));
					board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
					board.putUnitOn(x, y, 6, attackBase.unitArr.size() - 1, board);
					attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
					break;
				}	
				default: 
					break;
				}
			}
			else {
				
				switch (board.field[y * size + x].unitType) {
				case 0: {
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
							std::cout << "You can't move archer to this point(((\n";
							system("pause");
							attackBase.deleteUnit(oldX, oldY, board);
							break;
						}
						if (board.field[y * size + x].neutralPtr != NULL) {
							//	board.field[y * size + x].neutralPtr->effect(oldX, oldY, board.field[oldY * size + oldX].unitIndex);
							objector.p = board.field[y * size + x].neutralPtr;
							objector + *attackBase.unitArr[board.field[oldY * size + oldX].unitIndex];
							//std::cout << attackBase.unitArr[board.field[oldY * size + oldX].unitIndex]->damage;
							board.field[y * size + x].neutralPtr = NULL;
							//std::cout << attackBase.unitArr[board.field[oldY * size + oldX].unitIndex]->damage;
							system("pause");
						}
						if (attackBase.unitArr[board.field[oldY * size + oldX].unitIndex]->relocate(x, y, board, size)) {
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
							objector + *attackBase.unitArr[board.field[oldY * size + oldX].unitIndex];
							board.field[y * size + x].neutralPtr = NULL;
							system("pause");
						}
						if (attackBase.unitArr[board.field[y * size + x].unitIndex]->relocate(x, y, board, size)) {
							std::cout << "Ballista moved successfully!\n";
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
						objector + *attackBase.unitArr[board.field[oldY * size + oldX].unitIndex];
						board.field[y * size + x].neutralPtr = NULL;
						system("pause");
					}
					if (attackBase.unitArr[board.field[y * size + x].unitIndex]->relocate(x, y, board, size)) {
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
				if ((board.field[i * size + j].unitType == 5) || (board.field[i * size + j].unitType == 6)) {
					attackBase.unitArr[board.field[i * size + j].unitIndex]->relocate(j, i + 1, board, size);
					if (board.field[(i+1) * size + j].neutralPtr != NULL) {
						objector.p = board.field[y * size + x].neutralPtr;
						objector + *attackBase.unitArr[board.field[oldY * size + oldX].unitIndex];
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