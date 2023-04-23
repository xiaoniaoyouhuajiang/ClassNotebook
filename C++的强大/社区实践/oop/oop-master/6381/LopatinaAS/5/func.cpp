#include "func.h"
#include <cstdlib>
using namespace stepik;

void output (const vector<shared_ptr<Shape>>& arr) {
       for(const auto& i : arr){
            i->print();
            std::cout << std::endl;
       }
}

int compare(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b){ 
    return a->get_perimetr() < b->get_perimetr(); 
}

void sequencing (vector<shared_ptr<Shape>>& arr, int n){ //упорядочивание по периметру первых n фигур
    sort(arr.begin(), arr.begin()+n, compare); 
}

bool sum_prm (vector<shared_ptr<Shape>>& arr, int a1, int b1, int a2, int b2){
    int sum1 = 0, sum2 = 0;
    for (int i = a1; i<=b1; i++){
       sum1+=(*arr[i]).get_perimetr(); 
    }
    for (int i = a2; i<=b2; i++){
       sum2+=(*arr[i]).get_perimetr(); 
    }
    std::cout << "The first sum: " << sum1 << std::endl; 
    std::cout << "The second sum: " << sum2 << std::endl; 
    if (sum1 == sum2)
        return true;
    else return false; 
}