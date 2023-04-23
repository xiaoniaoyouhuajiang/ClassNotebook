#include "library.h"

void create(std::vector<Point> & coord, Point & center, int dots, std::string figure) {
    Point temp;
    std::cout << "Input " << dots << " coords of " << figure << " (x, y): " << std::endl;
    // вводим координаты фигуры
    for (int i = 0; i < dots; ++i) {
        std::cin >> temp.x;
        std::cin >> temp.y;
        coord.push_back(temp);
    }
    std::cout << "Inpute coords of center (x, y): " << std::endl;
    // вводим координаты центра
    std::cin >> center.x;
    std::cin >> center.y;
}
