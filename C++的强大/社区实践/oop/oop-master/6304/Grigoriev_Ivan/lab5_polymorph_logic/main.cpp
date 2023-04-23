#include <cstdlib>  //rand,srand
#include <ctime>
#include "testing.hpp"

int main() {
    Test_CheckRangesForEq_func();
    Test_DelElements_func();
    std::cout << "Testing is successful\n";
    my_impl::vector<my_impl::shared_ptr<Shape>> my_container = FillContainerWithRandShapes(1000); //filling
    PrintVectorOfShapes(my_container);
    PrintInfoAboutEq(my_container, 0, 2, 3, 5); //checking ranges for paralelograms number
    DelElements(my_container); //удаление фигур, вершины которых не лежат на осях x, y
    PrintVectorOfShapes(my_container);
    std::cout << "my_container after deleting (size = " << my_container.size() <<")\n";
    return 0;
}
