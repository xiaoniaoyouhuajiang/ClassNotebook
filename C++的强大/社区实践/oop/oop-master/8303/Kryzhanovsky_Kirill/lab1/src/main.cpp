#include <iostream>
#include <vector>
#include "GameField.h"
#include "Peon.h"
#include "Shooter.h"
#include "Elf.h"
#include "Witch.h"
#include "Goblin.h"
#include "Troll.h"

/**
 * Разработать и реализовать набор классов:
 + Класс игрового поля
 * Набор классов юнитов
 *
 * Игровое поле является контейнером для объектов представляющим прямоугольную сетку.
 * Основные требования к классу игрового поля:
 + Создание поля произвольного размера
 + Контроль максимального количества объектов на поле
 + Возможность добавления и удаления объектов на поле
 + Возможность копирования поля (включая объекты на нем)
 + Для хранения запрещается использовать контейнеры из stl
 *
 * Юнит является объектов, размещаемым на поля боя.
 * Один юнит представляет собой отряд.
 * Основные требования к классам юнитов:
 + Все юниты должны иметь как минимум один общий интерфейс
 + Реализованы 3 типа юнитов (например, пехота, лучники, конница)
 + Реализованы 2 вида юнитов для каждого типа(например, для пехоты могут быть созданы мечники и копейщики)
 + Юниты имеют характеристики, отражающие их основные атрибуты, такие как здоровье, броня, атака.
 + Юнит имеет возможность перемещаться по карте
 */


int main() {
    GameField* gameField = new GameField(10, 4);

    Peon* peon1 = new Peon();
    gameField->addUnit(peon1, 1, 1);
    gameField->printField();
    std::cout << std::endl;

    Peon* peon2 = new Peon();
    gameField->addUnit(peon2, 1, 0);
    gameField->printField();
    std::cout << std::endl;

    Shooter* shooter1 = new Shooter();
    gameField->addUnit(shooter1, 2, 0);
    gameField->printField();
    std::cout << std::endl;

    Elf* elf1 = new Elf();
    gameField->addUnit(elf1, 3, 0);
    gameField->printField();
    std::cout << std::endl;

    Witch* witch1 = new Witch();
    gameField->addUnit(witch1, 4, 0);
    gameField->printField();
    std::cout << std::endl;

    Troll* troll1 = new Troll();
    gameField->addUnit(troll1, 5, 0);
    gameField->printField();
    std::cout << std::endl;

    std::cout << "Add goblin" << std::endl;
    Goblin* goblin1 = new Goblin();
    gameField->addUnit(goblin1, 6, 0);
    gameField->printField();
    std::cout << std::endl;

    goblin1->print();

    std::cout << "Move goblin" << std::endl;

//    gameField->move(goblin1, 1, 1);
    goblin1->move(-1, 1);
    gameField->printField();


    std::cout << std::endl;
    goblin1->print();

//    shooter1->print();
//    peon1->print();
//
//    troll1->print();

//    elf1->print();
//    witch1->print();

    return 0;
}
