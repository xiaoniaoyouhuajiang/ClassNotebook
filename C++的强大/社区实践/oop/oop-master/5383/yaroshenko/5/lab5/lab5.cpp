#include "lab5.h"

Shape* generateRandomShape()
{
    int type = rand() % 4;

    switch (type)
    {
    case 0:
        return new Square(100);
    case 1:
        return new Rectangle(100);
    case 2:
        return new RightTriangle(100);
    case 3:
        return new IsoscelesTriangle(100);

    default:
        return nullptr;
    }
}

stepik::vector< stepik::shared_ptr<Shape> > generateShapes(size_t n)
{
    srand(time(NULL));
    stepik::vector< stepik::shared_ptr<Shape> > shapes(n);

    for (size_t i = 0; i < n; i++)
    {
        shapes[i] = stepik::shared_ptr<Shape>( generateRandomShape() );
    }

    return shapes;
}

stepik::shared_ptr<Shape> multipleSearch(
        const stepik::vector<stepik::shared_ptr<Shape> > &source,
        const stepik::vector<stepik::shared_ptr<Shape> > &possibleElements,
        std::function<bool (Shape*, Shape*)> condition)
{
    for (auto& shape_elem : source)
    {
        for (auto& cmp_elem : possibleElements)
        {
            if (condition(shape_elem.get(), cmp_elem.get()))
                return shape_elem;
        }
    }

    return stepik::shared_ptr<Shape>();
}

void divideVector(
        const stepik::vector<stepik::shared_ptr<Shape> > &source,
        stepik::vector<stepik::shared_ptr<Shape> > &part1,
        stepik::vector<stepik::shared_ptr<Shape> > &part2,
        std::function<bool (Shape*)> condition)
{
    for (auto& shape : source)
    {
        if (condition(shape.get()))
            part1.push_back(shape);
        else
            part2.push_back(shape);
    }
}
