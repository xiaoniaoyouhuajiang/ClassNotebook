#include <iostream>
#include <alg.hpp>

int main()
{
    Alg testSubject(1000);
    testSubject.fill();
    testSubject.nonChangingAlgorithm();
    testSubject.ChangingAlgorithm();

    return 0;
}
