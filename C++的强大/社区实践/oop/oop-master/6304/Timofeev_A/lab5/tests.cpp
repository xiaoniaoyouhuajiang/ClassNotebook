#include <cassert>

#include "vector.hpp"
#include "shared_ptr.hpp"
#include "figures.h"
#include "algs.hpp"

void TestNoMod(){
    stepik::vector<stepik::shared_ptr<Shape>> figures(4);
    figures[0] = stepik::shared_ptr<Shape>(new Rectangle(2.3, 3.2, 2.0, 1.0));
    figures[1] = stepik::shared_ptr<Shape>(new Rectangle(3.3, 3.2, 1.0, 2.0));
    figures[2] = stepik::shared_ptr<Shape>(new Rectangle(22.3, 3.2, 1.5, 1.0));
    figures[2] = stepik::shared_ptr<Shape>(new Rectangle(22.3, 3.2, 1.0, 0.5));
    double criterion = 5.5;
    assert(CriterionCheck(criterion, figures, 1, 2) == true);
    assert(CriterionCheck(criterion, figures, 2, 1) == false);
    cout << "NoMod tests with Rectangles completed!" << endl;

    figures[0] = stepik::shared_ptr<Shape>(new Pentagram(2.3, 3.2, 22.0));
    figures[1] = stepik::shared_ptr<Shape>(new Pentagram(3.3, 3.2, 10.0));
    figures[2] = stepik::shared_ptr<Shape>(new Pentagram(22.3, 3.2, 1.5));
    figures[2] = stepik::shared_ptr<Shape>(new Pentagram(22.3, 3.2, 1.0));
    criterion = 25.5;
    assert(CriterionCheck(criterion, figures, 1, 2) == true);
    assert(CriterionCheck(criterion, figures, 2, 1) == false);
    cout << "NoMod tests with Pentagrams completed!" << endl;
    
    figures[0] = stepik::shared_ptr<Shape>(new Pentagon(2.3, 3.2, 22.0));
    figures[1] = stepik::shared_ptr<Shape>(new Pentagon(3.3, 3.2, 10.0));
    figures[2] = stepik::shared_ptr<Shape>(new Pentagon(22.3, 3.2, 1.5));
    figures[2] = stepik::shared_ptr<Shape>(new Pentagon(22.3, 3.2, 1.0));
    criterion = 25.5;
    assert(CriterionCheck(criterion, figures, 1, 2) == true);
    assert(CriterionCheck(criterion, figures, 2, 1) == false);
    cout << "NoMod tests with Pentagons completed!" << endl;
}

int main(){
    TestNoMod();
    std::cout<<"All tests completed!" << endl;
    return 0;
}