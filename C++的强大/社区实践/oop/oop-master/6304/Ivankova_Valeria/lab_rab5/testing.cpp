#include "testing.h"
#include <typeinfo>

void Test_CheckRangesForEq_func() {
	my_impl::vector<my_impl::shared_ptr<Shape>> container;
    container.push_back(my_impl::shared_ptr<Pentagon>  (new Pentagon  (0, 0, 3, 4, 5, 6, 8, 10, 14, 13)));
    container.push_back(my_impl::shared_ptr<Rectangle> (new Rectangle (0, 0, 5, 6)));
    container.push_back(my_impl::shared_ptr<Pentagrama>(new Pentagrama(0, 0, 16)));
    container.push_back(my_impl::shared_ptr<Pentagon>  (new Pentagon  (0, 0, 3, 6, 7, 13, 6, 18, 8, 2)));
    cout << "Create vector with 4 figures\n";
    cout << "Container size: " << container.size() << "\n";
    assert( CheckRangesForEq(container, 0, 1, 2, 3));
    assert( CheckRangesForEq(container, 0, 2, 2, 3));
    assert( CheckRangesForEq(container, 2, 3, 0, 1));
    assert(!CheckRangesForEq(container, 0, 3, 0, 4));
    assert( CheckRangesForEq(container, 0, 0, 0, 0));
    assert( CheckRangesForEq(container, 0, 2, 1, 3));

    container.push_back(my_impl::shared_ptr<Pentagon>(new Pentagon(0, 0, 3, 4, 3, 7, 23, 13, 16, 21)));
	cout << "Add pentagon\n";
    cout << "Container size: " << container.size() << "\n";
    assert(!CheckRangesForEq(container, 0, 1, 2, 4));
    assert( CheckRangesForEq(container, 0, 3, 3, 4));
    assert( CheckRangesForEq(container, 0, 0, 4, 4));
}

void Test_DelElements_func() {
	my_impl::vector<my_impl::shared_ptr<Shape>> container;
    container.push_back(my_impl::shared_ptr<Pentagon>  (new Pentagon  (5.2, 6.73, 3, 4, 3, 5, 5, 12, 6, 11)));
    container.push_back(my_impl::shared_ptr<Rectangle> (new Rectangle (7, 0, 5, 6)));
    container.push_back(my_impl::shared_ptr<Pentagrama>(new Pentagrama(0, 58, 5)));
    container.push_back(my_impl::shared_ptr<Pentagon>  (new Pentagon  (23.5, 0, 3, 4, 30, 12, 13, 6, 3, 2)));

    cout << "Create vector with 4 figures\n";
    cout << "Container size: " << container.size() << "\n";
    DelElements(container);
	std::string type_name = typeid(*container[0]).name();
    assert(type_name.find("Rectangle") != std::string::npos);
    assert(container.size() == 2);
	cout << "Remove 2 figures\n";
    cout << "Container size: " << container.size() << "\n";
	
    container.push_back(my_impl::shared_ptr<Pentagon>(new Pentagon(23.5, 0.7, 3, 4, 3, 14, 2, 5, 6, 14)));
    container.push_back(my_impl::shared_ptr<Rectangle>(new Rectangle(0.7, 0.01, 5, 6)));
	cout << "Add 2 figures\n";
    cout << "Container size: " << container.size() << "\n";
	
    DelElements(container);
	cout << "Remove 2 figures\n";
    cout << "Container size: " << container.size() << "\n";
    type_name = typeid(*container[1]).name();
    assert(type_name.find("Pentagrama") != std::string::npos);
    assert(container.size() == 2);
}
