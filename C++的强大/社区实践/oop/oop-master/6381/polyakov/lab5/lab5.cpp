#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Shape.hpp"
#include "vector.hpp"
#include "shared_ptr.hpp"

stepik::vector< stepik::shared_ptr<Shape> > generateShapes(int n){
    stepik::vector< stepik::shared_ptr<Shape> > v(n);
    srand(time(NULL));
    for(int i = 0 ; i < n ; ++i){
        switch (rand() % 3) {
            case 0:
                v[i] = stepik::shared_ptr<Rectangle>(new Rectangle(rand() % 100, rand() % 100, rand() % 100));
                v[i]->setXY(rand() % 100, rand() % 100);
                v[i]->rotate((double)rand() / RAND_MAX * 100);
                break;
            case 1:
                v[i] = stepik::shared_ptr<Square>(new Square(rand() % 100, rand() % 100));
                v[i]->setXY(rand() % 100, rand() % 100);
                v[i]->rotate((double)rand() / RAND_MAX * 100);
                break;
            case 2:
                v[i] = stepik::shared_ptr<Ellipse>(new Ellipse(rand() % 100, rand() % 100, rand() % 100));
                v[i]->setXY(rand() % 100, rand() % 100);
                v[i]->rotate((double)rand() / RAND_MAX * 100);
                break;
        }
    }
    return v;
}

int findFirstSequence(double sq, int n, stepik::vector< stepik::shared_ptr<Shape> > vec){
    int k = 0;
    for(int i = 0 ; i < vec.size() ; ++i){
        if(k == n) return i - n;
        if(vec[i]->biggerSquare(sq)) ++k;
        else k = 0;
    }
    if(k == n) return vec.size() - n;
    else return -1;
}

void replaceElem(double sq, stepik::vector< stepik::shared_ptr<Shape> > &vec){
    for(int i = 0 ; i < vec.size() ; ++i){
        if(vec[i]->biggerSquare(sq)){
            vec[i]->setXY(0,0);
        }
    }
}

int main(){
    int number = 20;
    auto x = generateShapes(number);
    std::cout << "squares of generated shapes:\n";
    std::cout << "№\tfigure\t\tsquare\tcentre\n";
    for(int i = 0 ; i < number ; ++i){
        std::cout << i << "\t" << x[i]->getShape() << "\t" << x[i]->getSquare() << "\t(" << x[i]->getX() << ";" << x[i]->getY() << ")\n";
    }
    int res = findFirstSequence(2500,5,x);
    std::cout << "first sequence of lenth 5 with squares more than 2500: ";
    if(res == -1) std::cout << "not found\n";
    else std::cout << res << std::endl;
    replaceElem(2500, x);
    std::cout << "container after replacement:\n";
    std::cout << "№\tfigure\t\tcentre\tsquare\n";
    for(int i = 0 ; i < number ; ++i){
        std::cout << i << "\t" << x[i]->getShape() << "\t" << x[i]->getSquare() << "\t(" << x[i]->getX() << ";" << x[i]->getY() << ")\n";
    }
    return 0;
}
