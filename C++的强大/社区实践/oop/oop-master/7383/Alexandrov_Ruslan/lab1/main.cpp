#include <iostream>
#include <string>
#include "array.h"

using namespace std;

int main() {
    Array<int> a1(90);
    Array<int> a2(8);
    Array<int> a3(114);
    a1 = a2;
    Array<int> a4 = a1;
    Array<int> a5 = std::move(a3);
    return 0;
}