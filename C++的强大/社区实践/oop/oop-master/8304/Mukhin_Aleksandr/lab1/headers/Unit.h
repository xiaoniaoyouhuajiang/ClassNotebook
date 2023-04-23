#ifndef LAB1_UNIT_H
#define LAB1_UNIT_H
#include "Creator.h"
#include <memory>


class Creator;
/*!
 * @brief Абструктный класс юнита, определяющий общий интерфейс
 * @var Unit::x координата юнита по вертикали
 * @var Unit::y координата юнита по горизонтали
 */
class Unit {
public:
    int x = -1;
    int y = -1;
    virtual ~Unit() {};
    /*!
     * @brief Приветствует пользователя во время использования
     * @details Определена в каждом классе потомке
     * @return символ приветствия для текущего экземпляра
     */
    virtual char greeting() const = 0;
};

#endif
