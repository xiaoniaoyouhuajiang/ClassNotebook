#include <iostream>
#include "ShapeGenerator.h"
#include "ShapeAlgorithm.h"

#define MAX_AREA 10

using namespace std;

bool test_check_equal();

bool test_remove_area_greater();

int main() {
    auto generator = new ShapeGenerator;
    custom::vector<custom::shared_ptr<Shape>> shapes_first = generator->generate(1000);
    custom::vector<custom::shared_ptr<Shape>> shapes_second = generator->generate(1000);
    cout << "Немодифицирующий алгоритм:" << endl;
    if(ShapeAlgorithm::check_equal(shapes_first, shapes_second)) {
        cout << "   Суммы площадей фигур двух различных диапазанов размером " << shapes_first.size() << " и "
             << shapes_second.size() << " равны" << endl;
    } else {
        cout << "   Суммы площадей фигур двух различных диапазанов размером " << shapes_first.size() << " и "
             << shapes_second.size() << " различны" << endl;
    }
    cout << "Модифицирующий алгоритм" << endl;
    cout << "  1. Из диапазана размером " << shapes_first.size() << " были удалены все фигуры, чья площадь больше " <<
         MAX_AREA << ". Было удалено " << ShapeAlgorithm::remove_area_greater(shapes_first, MAX_AREA)
         << ", новый размер диапазона " << shapes_first.size() << endl;
    cout << "  2. Из диапазана размером " << shapes_second.size() << " были удалены все фигуры, чья площадь больше " <<
         MAX_AREA << ". Было удалено " << ShapeAlgorithm::remove_area_greater(shapes_second, MAX_AREA)
         << ", новый размер диапазона " << shapes_second.size() << endl;
    cout << endl << "\033[0;34m" << "Начало тестирования" << endl;
    if(test_check_equal() && test_remove_area_greater()) {
        cout << "\033[0;34m" << "Все тесты пройдены успешно!" << endl;
    }
    return 0;
}

bool test_check_equal() {
    custom::vector<custom::shared_ptr<Shape>> shapes_first;
    shapes_first.push_back(
            custom::shared_ptr<Shape>(new Ellipse(new Point(0, 0), 5, 3, new Color(0, 0, 0), 1))); // S = 15pi
    shapes_first.push_back(
            custom::shared_ptr<Shape>(new Ellipse(new Point(0, 0), 2, 5, new Color(0, 0, 0), 1))); // S = 10pi

    custom::vector<custom::shared_ptr<Shape>> shapes_second;
    shapes_second.push_back(custom::shared_ptr<Shape>(
            new EllipseSector(new Point(0, 0), 5, 5, 0, M_PI / 2, new Color(0, 0, 0), 1))); // S = 25pi / 4
    shapes_second.push_back(custom::shared_ptr<Shape>(
            new EllipseSector(new Point(0, 0), 5, 5, M_PI / 2, M_PI, new Color(0, 0, 0), 1))); // S = 25pi / 4
    shapes_second.push_back(custom::shared_ptr<Shape>(
            new EllipseSector(new Point(0, 0), 5, 5, M_PI, 3 * M_PI / 2, new Color(0, 0, 0), 1))); // S = 25pi / 4
    shapes_second.push_back(custom::shared_ptr<Shape>(
            new EllipseSector(new Point(0, 0), 5, 5, 3 * M_PI / 2, 2 * M_PI, new Color(0, 0, 0), 1))); // S = 25pi / 4
    if(ShapeAlgorithm::check_equal(shapes_first, shapes_second)) {
        cout << "\033[0;32m"
             << "Тестирование проверки двух диапазанов на равные площади пройдено успешна (в исходных диапазонах площади равны)"
             << "\033[0;0m" << endl;
    } else {
        cout << "\033[0;31m" << "Во время тестирования произошла ошибка!" << "\033[0;0m" << endl;
        return false;
    }
    shapes_second.push_back(custom::shared_ptr<Shape>(new Ellipse(new Point(0, 0), 5, 3, new Color(0, 0, 0), 1)));
    if(!ShapeAlgorithm::check_equal(shapes_first, shapes_second)) {
        cout << "\033[0;32m"
             << "Тестирование проверки двух диапазанов на равные площади пройдена успешно (в исходных диапазонах площади различны)"
             << "\033[0;0m" << endl;
    } else {
        cout << "\033[0;31m" << "Во время тестирования произошла ошибка!" << "\033[0;0m" << endl;
        return false;
    }
    return true;
}

bool test_remove_area_greater() {
    custom::vector<custom::shared_ptr<Shape>> shapes;
    shapes.push_back(custom::shared_ptr<Shape>(new Parallelogram(new Point(0, 0), new Point(10, 10),
                                                                 new Point(20, 10), new Color(0, 0, 0), 1))); // S = 100
    shapes.push_back(custom::shared_ptr<Shape>(new Parallelogram(new Point(0, 0), new Point(10, 10),
                                                                 new Point(20, 10), new Color(0, 0, 0), 2))); // S = 100
    shapes.push_back(custom::shared_ptr<Shape>(new Parallelogram(new Point(0, 0), new Point(10, 10),
                                                                 new Point(20, 10), new Color(0, 0, 0), 3))); // S = 100
    if(ShapeAlgorithm::remove_area_greater(shapes, 99) == 3) {
        cout << "\033[0;32m"
             << "Тестирование проверки удаления всех элементов, чья площадь больше определенного значения, пройдено успешно"
             << "\033[0;0m" << endl;
    } else {
        cout << "\033[0;31m" << "Во время тестирования произошла ошибка!" << "\033[0;0m" << endl;
        return false;
    }
    return true;
}