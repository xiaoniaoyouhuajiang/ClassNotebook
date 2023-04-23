#include "shared_ptr.h"

using namespace std;
using stepik::shared_ptr;

int main()
{
    int* ptr1 = new int(10);
    shared_ptr<int> shared_ptr1(ptr1);
    shared_ptr<int> shared_ptr2(shared_ptr1);
    cout << "shared_ptr1.use_count(): " << shared_ptr1.use_count() << endl;
    int* ptr2 = new int(2);
    shared_ptr2.reset(ptr2);
    cout << "shared_ptr1.use_count(): " << shared_ptr1.use_count() << endl;
    cout << "shared_ptr2.use_count(): " << shared_ptr2.use_count() << endl;
    if(shared_ptr1 == shared_ptr2)
        cout << "shared_ptr1 == shared_ptr2" << endl;
    else
        cout << "shared_ptr1 != shared_ptr2" << endl;
    shared_ptr1.swap(shared_ptr2);
    cout << "*shared_ptr1 == " << *shared_ptr1 << endl;
    cout << "*shared_ptr1 == " << *shared_ptr2 << endl;
    return 0;
}
