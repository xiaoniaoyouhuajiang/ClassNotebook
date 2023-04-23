#include "algorithms.hpp"

//печать вектора
void PrintVectorOfShapes(const my_impl::vector<my_impl::shared_ptr<Shape>>& vector) {
        for(const auto& item : vector)
            std::cout << *item;
}

//заполнение вектора
my_impl::vector<my_impl::shared_ptr<Shape>> FillContainerWithRandShapes(size_t size) {
    my_impl::vector<my_impl::shared_ptr<Shape>> my_container(size);
    srand(time(nullptr));
    int which_figure_is_next = 0;
    for(auto& item : my_container) {
        which_figure_is_next = rand()%3 + 1;
        if(which_figure_is_next == 1)
            item = my_impl::shared_ptr<Shape>
            (new paralelogram (rand()%41-20, rand()%41-20, rand()%10+1, rand()%10+1, rand()%70 + 20));
        else if(which_figure_is_next == 2)
            item = my_impl::shared_ptr<Shape>
            (new ellipse (rand()%41-20, rand()%41-20, rand()%10+1, rand()%10+1));
        else if(which_figure_is_next == 3) {
            int x = rand()%41-20;
            int y = rand()%41-20;
            int r1 = rand()%10+1;
            int r2 = rand()%10+1;
            item = my_impl::shared_ptr<Shape>
            (new ellipseSECTOR (x, y, r1, r2, {double(x), double(y + std::min(r1,r2))}, {double(x + std::max(r1,r2)),double(y)}));
        }
    }
    return my_container;
}

//Проверка двух неупорядоченных диапазонов на равенство по определенному критерию.
//критерий: кол-во паралеллограммов
bool CheckRangesForEq(const my_impl::vector<my_impl::shared_ptr<Shape>>& vec,
        size_t pos1_1, size_t pos1_2, size_t pos2_1, size_t pos2_2)
{
    int count1 = 0, count2 = 0;
    for(int i = pos1_1; i <= pos1_2; ++i){
        std::string type_name = typeid(*vec[i]).name();
        if(type_name == "12paralelogram")
            count1++;
    }
    for(int i = pos2_1; i <= pos2_2; ++i){
        std::string type_name = typeid(*vec[i]).name();
        if(type_name == "12paralelogram")
            count2++;
    }
    if(count1 == count2) {
        return true;
    }
    return false;
}

void PrintInfoAboutEq(const my_impl::vector<my_impl::shared_ptr<Shape>>& vec,
        size_t pos1_1, size_t pos1_2, size_t pos2_1, size_t pos2_2) {
    if(CheckRangesForEq(vec, pos1_1, pos1_2, pos2_1, pos2_2))
        std::cout << "Range1 : [" <<pos1_1 <<", " <<pos1_2
        <<"] = Range2 : [" <<pos2_1 <<", " <<pos2_2 <<"]\n";
    else
        std::cout << "Range1 : [" <<pos1_1 <<", " <<pos1_2
        <<"] != Range2 : [" <<pos2_1 <<", " <<pos2_2 <<"]\n";
}
//Удалить элементы, удовлетворяющие заданному критерию.
//критерий: центр фигуры только на осях
void DelElements(my_impl::vector<my_impl::shared_ptr<Shape>>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        if((vec[i].get()->getCentre().x != 0) && (vec[i].get()->getCentre().y != 0)) {
            vec.erase(vec.begin() + i);
            i--;
        }
    }
}