#include "../../2/src/ellipse.h"
#include "../../2/src/square.h" // + rectangle.h
#include "../../3/list.h"
#include "../../4/shared_ptr.h"
#include <functional>

namespace stepik
{

const int BOUND = 20;
bool predicate(Shape* shape)
{
    // расстояние от начала координат до ближайшей вершины больше 20
    return (shape->distance(Point()) > BOUND);
}


list_iterator< shared_ptr<Shape> > search_n(
        const list< shared_ptr<Shape> >& container,
        size_t count,
        std::function<bool (Shape*)> pred)
{
    size_t curr_count = 0;

    list_iterator< shared_ptr<Shape> > result,
            first = container.begin(),
            last = container.end();



    for (; first != last; first++)
    {
        curr_count = 0;


        while (pred(first->get()))
        {
            curr_count++;
            if (curr_count == 1)
               result = first;
            if (curr_count == count)
            return result;
        }
        first ++;
    }

}


list< shared_ptr<Shape> > copy_if(
        const list< shared_ptr<Shape> >& container,
        std::function<bool (Shape*)> pred)
{
    list< shared_ptr<Shape> > result;
    list_iterator< shared_ptr<Shape> > first = container.begin(), last = container.end();

    while (first != last)
    {
        if (pred(first->get()))
        {
            result.push_back(*first);
        }
        first++;
    }

    return result;
}


}
