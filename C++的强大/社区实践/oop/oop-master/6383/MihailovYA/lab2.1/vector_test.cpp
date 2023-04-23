#include <iostream>
#include "vector.h"

using namespace stepik;

int main(){
        vector<int> p(10);
        p.print();
        p.resize(5);
        p.print();
        return 0;
}
