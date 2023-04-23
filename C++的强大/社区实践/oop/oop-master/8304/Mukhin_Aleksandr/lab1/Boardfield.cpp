#include <CavalryJuniorCreator.h>
#include <CavalrySeniorCreator.h>
#include <ArchersJuniorCreator.h>
#include <ArchersSeniorCreator.h>
#include <InfantryJuniorCreator.h>
#include <InfantrySeniorCreator.h>
#include "Boardfield.h"

/*!
 * @brief Конструктор принимает ширину и длину поля и выделяет память под все необходимые данные
 * @param length длина поля
 * @param width ширина поля
 */
Boardfield::Boardfield(int length, int width) {
    this->length = length;
    this->width = width;

    repository = Array<Array<std::shared_ptr<Unit>>>(length);

    for (size_t i = 0; i < length; i++) {
        repository[i] = Array<std::shared_ptr<Unit>>(width);
    }
}

/*!
 * @brief С помощью итератора выводит игровое поле на экран
 */
void Boardfield::get_board() {
    for (const auto& row : repository) {
        for (const auto& item : row) {
            std::cout << item << "    ";
        }
        std::cout << std::endl;
    }
}

/*!
 * @brief Проверяет, есть ли свободное место на доске
 * @return true, есть есть, false - в другом случае
 */
bool Boardfield::is_free_space() {
    return length * width > unit_amount_on_the_board;
}

/*!
 * @brief Удаляет юнит с доски
 * @param x координата по вертикали
 * @param y координата по горизонтали
 * @return true, если функция успешно выполнила свою задачу, false - в другом случае
 */
bool Boardfield::delete_unit(int x, int y) {
    if (!is_valid_coord(x, y) || repository[x][y] == nullptr) {
        return false;
    }
    repository[x][y] = nullptr;
    --unit_amount_on_the_board;
    return true;
}

/*!
 * @brief Проверяет валидность переденных координат
 * @param x координата по вертикали
 * @param y координата по горизонтали
 * @return true, если координаты валидные, false - в другом случае
 */
bool Boardfield::is_valid_coord(int x, int y) {
    return x >= 0 && x < length && y >= 0 && y < width;
}

/*!
 * @brief Добавляет Unit на первую свободную позицию
 * @param key показатель того, какой именно Unit будет создан
 * @return true, если функция успешно выполнила свою задачу, false - в другом случае
 */
bool Boardfield::add_unit_random(int key) {
    std::shared_ptr<Unit> unit = get_unit(key);
    if (unit != nullptr) {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (repository[i][j] == nullptr) {

                    repository[i][j] = unit;
                    repository[i][j]->x = i;
                    repository[i][j]->y = j;

                    ++unit_amount_on_the_board;
                    return true;
                }
            }
        }
    }
    return false;
}

/*!
 * @brief Возвращает конкретный Unit взависимости от переданного ключа
 * @param key показатель того, какой именно Unit будет создан
 * @return умный указатель на созданный Unit
 */
std::shared_ptr<Unit> Boardfield::get_unit(int key) {
    if (is_free_space()) {
        Creator* tmp = nullptr;
        std::shared_ptr<Creator> return_pointer;

        switch (key) {
            case 0:
                tmp = new CavalryJuniorCreator();
                break;
            case 1:
                tmp = new CavalrySeniorCreator();
                break;
            case 2:
                tmp = new ArchersJuniorCreator();
                break;
            case 3:
                tmp = new ArchersSeniorCreator();
                break;
            case 4:
                tmp = new InfantryJuniorCreator();
                break;
            case 5:
                tmp = new InfantrySeniorCreator();
                break;
            default:
                throw std::out_of_range("Wrong param, read documentation before");
        }

        return_pointer = std::shared_ptr<Creator>(tmp);
        tmp = nullptr;

        return return_pointer->make_unit();
    }
    return nullptr;
}

/*!
 * @brief Добавляет Unit на конкретную позицию
 * @param x координата по вертикали
 * @param y координата по горизонтали
 * @param key показатель того, какой именно Unit будет создан
 * @return true, если функция успешно выполнила свою задачу, false - в другом случае
 */
bool Boardfield::add_unit_at(int key, int x, int y) {
    std::shared_ptr<Unit> unit = get_unit(key);
    if (unit != nullptr && is_valid_coord(x, y) && repository[x][y] == nullptr) {
        repository[x][y] = unit;
        repository[x][y]->x = x;
        repository[x][y]->y = y;

        ++unit_amount_on_the_board;
        return true;
    }
    return false;
}

/*!
 * @brief Передвигает существующий юнит с одного места на другое
 * @param old_x старая координата по вертикали
 * @param old_y старая координата по горизонтали
 * @param dest_x новая координата по вертикали
 * @param dest_y новая координата по горизонтали
 * @return true, если функция успешно выполнила свою задачу, false - в другом случае
 */
bool Boardfield::move(int old_x, int old_y, int dest_x, int dest_y) {
    if (!is_valid_coord(old_x, old_y) || !is_valid_coord(dest_x, dest_y) ||
            repository[old_x][old_y] == nullptr || repository[dest_x][dest_y] != nullptr) {
        return false;
    }

    repository[dest_x][dest_y] = std::shared_ptr<Unit>(repository[old_x][old_y]);
    repository[old_x][old_y] = nullptr;
    return true;
}
