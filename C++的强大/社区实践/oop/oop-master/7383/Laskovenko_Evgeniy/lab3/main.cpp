#include <iostream>
#include "list.h"
#include "vector.h"

using namespace std;

int main()
{
    list<int> a;
    a.push_back(5);
    a.push_front(3);
    vector<int> b({1, 2, 3, 4, 5});

    return 0;
}
