#include "lab5.h"

bool search_predicate(Shape* s, Shape* cmp)
{
    return (s->area() < cmp->area());
}

bool divide_predicate(Shape* s)
{
    return (s->area() > 100);
}

int main()
{
    stepik::vector< stepik::shared_ptr<Shape> > shapes = generateShapes(1000);

    // несколько заданных фигур для поиска
    stepik::vector< stepik::shared_ptr<Shape> > searchShapes =
    {
        stepik::shared_ptr<Shape>(new Square(Point2d(), 25)),
        stepik::shared_ptr<Shape>(new Rectangle(Point2d(), 30, 40)),
        stepik::shared_ptr<Shape>(new RightTriangle(Point2d(), 10, 30))
    };

    // ищем первую фигуру из нескольких по критерию
    stepik::shared_ptr<Shape> searchResult = multipleSearch(shapes, searchShapes, search_predicate);

    // разбиваем массив на 2 части по критерию
    stepik::vector< stepik::shared_ptr<Shape> > part1, part2;
    divideVector(shapes, part1, part2, divide_predicate);

    return 0;
}
