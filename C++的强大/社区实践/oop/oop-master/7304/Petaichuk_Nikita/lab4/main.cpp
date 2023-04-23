#include <iostream>
#include "stepik_clever_pointers.h"

using namespace stepik;
using std::cout;
using std::endl;

int main()
{
    shared_ptr<int> first(new int(9));
    shared_ptr<int> second = first;
    shared_ptr<int> third;
    third = second;

    cout << first.use_count() << " pointers on the element '" << *(second.get()) << "'." << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;

    shared_ptr<int> another_pointer(new int(4));
    third.reset(another_pointer.get());
    cout << "Shared_ptr vulnerability:" << endl;
    if (another_pointer == third)
        cout << "Pointers use same pointers (" << another_pointer.get() << " == "
             << third.get() << "), but" << endl;
    cout << "'Third' count - " << third.use_count() << endl
         << "'Another_pointer' count - " << another_pointer.use_count() << endl;
    return 0;
}
