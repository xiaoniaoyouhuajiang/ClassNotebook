#include <iostream>
#include "array.h"

using namespace std;

void memory_list(Array<int>& a)
{
    if(a.get_array())
    {
        cout << "False.\n\tMemory list: ";
        for(unsigned i=0; i<a.size(); i++)
            cout << "\n\t\t[" << i << "] = " << ' ' << &a[i] << ' ';
    }
    else
        cout << "True.";
}

int main()
{
    Array<int> a(5);
    cout << "Default constructor a(5):\n\tSize of 'a': " << a.size();
    cout << "\n\t'a' is nullptr? ";
    memory_list(a);

    Array<int> b(a);
    cout << "\n\nCopy constructor b(a):\n\tSize of 'b': " << b.size();
    cout << "\n\t'b' is nullptr? ";
    memory_list(b);

    Array<int> c(move(a));
    cout << "\n\nMove constructor c(move(a)):\n\tSize of 'c': " << c.size();
    cout << "\n\t'c' is nullptr? ";
    memory_list(c);
    cout << "\n\tSize of 'a': " << a.size();
    cout << "\n\t'a' is nullptr? ";
    memory_list(a);

    c = b;
    cout << "\n\nOperator '=' (c = b):\n\tSize of 'c': " << c.size();
    cout << "\n\t'c' is nullptr? ";
    memory_list(c);
    cout << "\n\tSize of 'b': "<< b.size();
    cout << "\n\t'b' is nullptr? ";
    memory_list(b);
    cout << endl;

    return 0;
}
