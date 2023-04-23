#include <iostream>
#include <string>

#include "lab5.h"

using namespace stepik;

void printList(list< shared_ptr<Shape> > &container, std::string name)
{
    std::cout << "List #" + name + ":" << std::endl;
    for(list_iterator< shared_ptr<Shape> > it = container.begin();
        it != container.end(); it++)
    {
          (*it)->print(std::cout);
    }
    std::cout << std::endl << "-----------------" << std::endl;

}

int main(/*int argc, char *argv[]*/)
{
    list< shared_ptr<Shape> > container1  = createRandomShapeList(10);
    list< shared_ptr<Shape> > container2  = createRandomShapeList(10);

    std::cout << std::endl << "Origin Lists:" << std::endl;

    printList(container1, "Container 1");
    printList(container2, "Container 2");
    std::cout << std::endl << "-----------------" << std::endl;

    std::cout << std::endl << "Nonmodify Algorithm:" << std::endl;
    bool isAssign = checkLists(container1, container2, isEqual);
    if(isAssign)
    {
        std::cout << "Containers are equal" << std::endl;
    }
    else
    {
        std::cout << "Containers are different" << std::endl;
    }


    std::cout << std::endl << "Modify Algorithm:" << std::endl;
    eraseElement(container1, redis);
    eraseElement(container2, redis);

    return 0;
}
