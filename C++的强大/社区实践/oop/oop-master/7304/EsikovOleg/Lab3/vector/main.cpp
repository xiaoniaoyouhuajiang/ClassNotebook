#include "myvector.h"

using namespace stepik;
using std::cout;

int main()
{
    vector<int> a(5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    cout << "vector a: " << a;
    a.erase(a.end());
    cout << "a.erase(a.end()): " << a;
    a.push_back(10);
    cout << "a.push_back(10): " << a;
    a.insert(a.begin(), 5);
    cout << "a.insert(a.begin(), 5): " << a;
    vector<int> b(a);
    cout << "vector b(a): " << b;
    vector<int> c(8);
    c = a;
    cout << "vector c(8); c = a: " << c;
    vector<int> d = {9, 8, 7};
    cout << "vecotr d: " << d;
    c.insert(c.begin() + 2, d.begin(), d.end());
    cout << "c.insert(c.begin() + 2, d.begin(), d.end()): " << c;
    c.assign(a.begin(), a.end());
    cout << "c.assign(a.begin(), a.end()): " << c;

    return 0;
}
