#include <iostream>

#include <iostream>
#include <random>
#include <chrono>

#include "shape/Shape.h" //я всё положил в один хэдер, чтобыы не писать много строк
#include "shared_ptr.h"
#include "vec.h"

//Проверка что ни один элемент диапазона не соответствует заданному критерию
//Скопировать элементы, за исключением тех, кто удовлетворяет критериюю

void gen( custom::vector< custom::shared_ptr<custom::Shape> >* arr )
{
    std::random_device rd;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt;
    mt.seed( rd.entropy() ? rd() : seed );

    std::uniform_int_distribution<int> rndnum(0, 255);
    std::uniform_int_distribution<int> class_type(0, 2);

    for( size_t i = 0; i < 1000; ++i )
    {
        switch (class_type(mt))
        {
            case 0:
            {
                custom::Shape* bc = new custom::Segment( rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), "Белый" );
                arr->push_back(custom::shared_ptr<custom::Shape>(bc));
                break;
            }
            case 1:
            {
                custom::Shape* bp = new custom::Pentagon( rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), "Белый" );
                arr->push_back(custom::shared_ptr<custom::Shape>(bp));
                break;
            }
            case 2:
            {
                custom::Shape* bp = new custom::Ellipse( rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), rndnum(mt), "Белый" );
                arr->push_back(custom::shared_ptr<custom::Shape>(bp));
                break;
            }
        }
    }
}

bool check( custom::vector< custom::shared_ptr<custom::Shape> >& arr, size_t bpos, size_t epos)
{
    if( epos > arr.size() - 1 ) return false;
    for(; bpos < epos; ++bpos )
    {
        if( arr[bpos].get()->X == 0 && arr[bpos].get()->Y == 0 ) // просто проверка на то, что Shape находится в точке (0,0) (для этого их пришлось вынести в public)
            return false;
    }
    return true;
}

custom::vector< custom::shared_ptr<custom::Shape> > copy(custom::vector< custom::shared_ptr<custom::Shape> > arr)
{
    custom::vector< custom::shared_ptr<custom::Shape> > out;
    for( auto& c : arr )
    {
        if( !(c.get()->Angle == 213) )
        {
            out.push_back(c);
        }
    }
    return out;
}

int main()
{
    custom::vector< custom::shared_ptr<custom::Shape> > arr;
    gen(&arr);
    int beg, end;
    std::cout << "Введите диапазон проверки значений (0;" << arr.size() - 1 << ")\n" ;
    std::cin >> beg >> end;

    if( check(arr, beg, end) )
        std::cout << "Нет совпадений\n\n";
    else
        std::cout << "Eсть совпадения\n\n";

    custom::vector< custom::shared_ptr<custom::Shape> > second;

    second = copy(arr);

    std::cout << "Copied el:\n";

    for( auto& c : second )
    {
        std::cout << "There is an element\n";
    }
}
