#include "vector.hpp"
#include "shared.hpp"
#include "figure.hpp"
#include "algs.hpp"

using namespace last;


int main(){
    vector<shared_ptr<Shape>> mass=create();
    if(allsquareless(mass,0))
        std::cout<<"Ни один элемент диапазона не обладает площадью меньше заданного"<<\n";
    else
        std::cout<<"Есть элементы, площадь которых меньше заданного\n";
    copyBad(mass, 100);
    std::cout<<"Размер контейнера после модифицирующего алгоритма "<<mass.size()<<"\n";
    return 0;
}