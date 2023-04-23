#ifndef LAB1_BOARDFIELD_H
#define LAB1_BOARDFIELD_H
#include "Unit.h"
#include "Array.hpp"
#include <memory>
#include "CavalryJuniorCreator.h"
#include "Iterator.hpp"

/*!
 * @brief Класс игрового поля
 * @var Boardfield::length переменная, определяющая длину игрового поля
 * @var Boardfield::width переменная, определяющая ширину игрового поля
 * @var Boardfield::unit_amount_on_the_board переменная, определяющая общее количество юнитов на игровом поле
 * @var Boardfield::repository переменная, хранящая двойной массив умных указателей на каждую клетку поля
 */
class Boardfield {
private:
    int length = 0;
    int width = 0;
    int unit_amount_on_the_board = 0;
    Array<Array<std::shared_ptr<Unit>>> repository;
    bool is_valid_coord(int x, int y);
    std::shared_ptr<Unit> get_unit(int key);

public:
    Boardfield(int length, int width);
    bool add_unit_at(int key, int x, int y);
    bool add_unit_random(int key);
    void get_board();
    bool is_free_space();
    bool delete_unit(int x, int y);
    bool move(int old_x, int old_y, int dest_x, int dest_y);
};

#endif
