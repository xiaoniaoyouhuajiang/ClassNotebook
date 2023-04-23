#include "list.h"

using namespace stepik;
using namespace std;

int main()
{
    list<int> a;
    cout << "step 1: " << a;
    a.push_back(3);
    a.push_back(6);
    a.push_back(9);
    a.push_front(2);
    a.push_front(1);
    cout << "step 2: " << a;
    list<int> b(a);
    b.pop_back();
    cout << "step 3: " << b;
    a.clear();
    a.push_back(0);
    cout << "step 4: " << a;
    if(a.begin() == b.begin())
        cout << "step 5: a.begin() == c.begin()" << endl;
    else
        cout << "step 5: a.begin() != c.begin()" << endl;
    a.insert(++a.begin(), 7);
    cout << "step 6: " << a;
    return 0;
}
