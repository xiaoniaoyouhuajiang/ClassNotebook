#include <iostream>
#include <random>
#include <chrono>

#include "shapes.hpp"
#include "shared_ptr.hpp"
#include "vector.hpp"

//Поиск первого из нескольких возможных элементов по заданному критерию.
//Скопировать элементы, удовлетворяющие критерию.

void gen(custom::vector<custom::shared_ptr<Shape>> *arr) {
    std::random_device rd;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt;
    mt.seed(rd.entropy() ? rd() : seed);

    std::uniform_int_distribution<int> rndnum(0, 255);
    std::uniform_int_distribution<int> class_type(0, 1);

    for (size_t i = 0; i < 1000; ++i) {
        switch (class_type(mt)) {
            case 0: {
                Shape *bc = new Triangle(1, 1, 2, 2, 3, 3);
                bc->setColor("black");
                arr->push_back(custom::shared_ptr<Shape>(bc));
                break;
            }
            case 1: {
                Shape *bp = new Rectangle(1, 1, 2, 2, 3, 3, 4, 4);
                bp->setColor("black");
                arr->push_back(custom::shared_ptr<Shape>(bp));
                break;
            }
        }
    }
}

int find(float square, custom::vector<custom::shared_ptr<Shape>> arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if ((arr[i].get()->getSquare() == square)) return i;
    }
    return -1;
}

size_t copy(char r, char g, char b, custom::vector<custom::shared_ptr<Shape>> *source) {
    size_t size = source->size();
    for (size_t i = 0; i < size; ++i) {
        string temp = source->at(i).get()->getColor();
        source->push_back(source->at(i));
    }
    return source->size();
}

void print(custom::vector<custom::shared_ptr<Shape>> input, size_t begin) {
    for (; begin < input.size(); ++begin) {
        input[begin].get()->getLocation();
    }
}

int main() {
    custom::vector<custom::shared_ptr<Shape>> arr;
    gen(&arr);

    float square;
    std::cin >> square;
    int ind;
    if ((ind = find(square)) != -1)
        std::cout << *arr[ind].get() << '\n';
    else
        std::cout << "Not" << '\n';

    char r, g, b;
    size_t size = arr.size();
    std::cin >> r >> g >> b;
    copy(r, g, b, &arr);
    if (size != arr.size()) {
        std::cout << "Smth changed";
        print(arr, size);
    }
    return 0;
}