#include "mylist.h"

using namespace stepik;
using std::cout;
using std::endl;

int main()
{
    list<int> a;
    cout << "a: " << a;
    a.push_back(10);
    cout << "a.push_back(10): " << a;
    a.push_back(5);
    cout << "a.push_back(5): " << a;
    a.push_front(1);
    cout << "a.push_front(1): " << a;
    a.pop_front();
    cout << "a.pop_front(): " << a;
    list<int> b(a);
    cout << "b(a): " << b;
    a.clear();
    cout << "a.clear(): " << a;
    list<int> c(b);
    cout << "c(b): " << c;
    c = a;
    cout << "c=a: " << c;
    if(a.begin() == c.begin())
        cout << "a.begin() == c.begin()" << endl;
    else
        cout << "a.begin() != c.begin()" << endl;
    c.insert(c.begin(), 8);
    cout << "c.insert(c.begin(), 8): " << c;
    cout << "a:" << a;
    if(a.begin() == c.begin())
        cout << "a.begin() == c.begin()" << endl;
    else
        cout << "a.begin() != c.begin()" << endl;
    c.push_back(20);
    cout << "c.push_back(20): " << c;
    c.push_front(3);
    cout << "c.push_front(3): " << c;
    c.insert(++c.begin(), 1);
    cout << "c.insert(++c.begin(), 1): " << c;

    return 0;
}
