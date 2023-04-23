#include <chrono>
#include <random>
#include <functional>
#include <cmath>
#include <iostream>
#include "shapes.h"

#include "vector.h"
#include "shared_ptr.h"

#ifdef _MANUAL_TEST
#define SHAPECOUNT 10
#else
#define SHAPECOUNT 1000
#endif

etuoop::vector< etuoop::shared_ptr< etuoop::Shape> >
findShapes(etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > source,
           size_t count,
           std::function<bool (etuoop::Shape*)> cond)
{
    etuoop::vector< etuoop::shared_ptr< etuoop::Shape> > r;
    size_t found = 0;
    for (auto& it : source) {
        if (found == count) { break; }
        if (cond(it.get())) {
            r.push_back(it);
            ++found;
        }
    }
    return r;
}

etuoop::vector< etuoop::shared_ptr< etuoop::Shape> >
copyShapes(etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > source,
           std::function<bool (etuoop::Shape*)> cond)
{
    etuoop::vector< etuoop::shared_ptr< etuoop::Shape> > r;
    for (auto& it : source) {
        if (cond(it.get())) {
            r.push_back(etuoop::shared_ptr< etuoop::Shape> (it->clone()) );
        }
    }
    return r;
}

int main(int argc, char const *argv[])
{
    etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > shapes(SHAPECOUNT);
    for (auto& it : shapes) {
        it = etuoop::shared_ptr< etuoop::Shape >(etuoop::Shape::createRandom({
            etuoop::Square::createRandom,
            etuoop::Rectangle::createRandom,
            etuoop::Ellipse::createRandom
        }));
    }

    etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > foundShapes = findShapes(
                shapes, 250,
    [](etuoop::Shape * shape)->bool {
        return (shape->getArea() > (1 << 14));
    }
            );

    etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > copiedShapes = copyShapes(
                shapes,
    [](etuoop::Shape * shape)->bool {
        return (shape->getPerimeter() > (1 << 9));
    }
            );

#ifdef _MANUAL_TEST
    std::cout << "shapes:" << std::endl;
    for (auto& it : shapes) {
        std::cout << *it << std::endl;
    }
    std::cout << "foundShapes:" << std::endl;
    for (auto& it : foundShapes) {
        std::cout << *it << std::endl;
    }
    std::cout << "copiedShapes:" << std::endl;
    for (auto& it : copiedShapes) {
        std::cout << *it << std::endl;
    }
#endif

    return 0;
}
