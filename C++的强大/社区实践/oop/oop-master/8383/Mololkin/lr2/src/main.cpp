// OOP_lr_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <utility>
#include "GameBoard.h"
#include "Shooters.h"
#include "IUnit.h"
#include "BoardBuilder.h"
#include "Landscapes.h"
#include "NeutralObjects.h"


int main()
{
    //GameBoard board2 = board;
    //BoardBuilder::printBoard(board);
    //GameBoard* board1 = BoardBuilder::createBoard(12, 12);
    BoardBuilder::showExamples();
    IUnit* unit = new Spearman(5);
    Hospital* hosp = new Hospital();
    Spearman* spear = static_cast<Spearman*>(unit);
    spear->print();
    //ILandscape* landScape = new Hills();
    //std::cout << landScape -> canGo();
    /*board->printBoard();
    board->addUnit(IUnit::createUnit(Units::ARCHER), std::pair<int, int>(5, 5));
    std::cout << "----------------------------------------------------------------\n";
    board->printBoard();
    std::cout << "----------------------------------------------------------------\n";
    GameBoard copyBoard(board);
    copyBoard.moveUnit(std::pair<int, int>(5, 5), std::pair<int, int>(0, 0));
    copyBoard.printBoard();
    std::cout << "----------------------------------------------------------------\n";*/
    //board.printBoard();
    /*board->moveUnit(std::pair<int, int>(5, 5), std::pair<int, int>(0,0));
    board->printBoard();
    std::cout << "----------------------------------------------------------------\n";
    board->delUnit(std::pair<int, int>(8, 8));
    board->printBoard();*/
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
