#include "testing.hpp"

void Test_CheckRangesForEq_func() {
    my_impl::vector<my_impl::shared_ptr<Shape>> container;
    container.push_back(my_impl::shared_ptr<paralelogram>(new paralelogram (0, 0, 3, 4, 30)));
    container.push_back(my_impl::shared_ptr<ellipse>(new ellipse (0, 0, 5, 6)));
    container.push_back(my_impl::shared_ptr<ellipse>(new ellipse (0, 0, 5, 6)));
    container.push_back(my_impl::shared_ptr<paralelogram>(new paralelogram (0, 0, 3, 4, 30)));
    assert(CheckRangesForEq(container, 0, 1, 2, 3));
    assert(CheckRangesForEq(container, 0, 2, 2, 3));
    assert(CheckRangesForEq(container, 2, 3, 0, 1));
    assert(!CheckRangesForEq(container, 0, 3, 0, 2));
    assert(CheckRangesForEq(container, 0, 0, 0, 0));
    assert(CheckRangesForEq(container, 0, 2, 1, 3));
    container.push_back(my_impl::shared_ptr<paralelogram>(new paralelogram (0, 0, 3, 4, 30)));
    assert(!CheckRangesForEq(container, 0, 1, 2, 4));
    assert(CheckRangesForEq(container, 0, 3, 3, 4));
    assert(CheckRangesForEq(container, 0, 0, 4, 4));
}

void Test_DelElements_func() {
    my_impl::vector<my_impl::shared_ptr<Shape>> container;
    container.push_back(my_impl::shared_ptr<paralelogram>(new paralelogram (5.2, 6.73, 3, 4, 30)));
    container.push_back(my_impl::shared_ptr<ellipse>(new ellipse (7, 0, 5, 6)));
    container.push_back(my_impl::shared_ptr<ellipse>(new ellipse (0, 58, 5, 6)));
    container.push_back(my_impl::shared_ptr<paralelogram>(new paralelogram (23.5, 0, 3, 4, 30)));
    DelElements(container);
    std::string type_name = typeid(*container[0]).name();
    assert(type_name == "7ellipse");
    assert(container.size() == 3);
    container.push_back(my_impl::shared_ptr<paralelogram>(new paralelogram (23.5, 0.7, 3, 4, 30)));
    container.push_back(my_impl::shared_ptr<ellipse>(new ellipse (0.7, 0.01, 5, 6)));
    DelElements(container);
    type_name = typeid(*container[2]).name();
    assert(type_name == "12paralelogram");
    assert(container.size() == 3);
    //vector now ellipse(7,0), ellipse (0,58), paralelogram(23.5, 0)
    (*container[0]).MoveFigure(8, 1);
    (*container[1]).MoveFigure(1, 1);
    (*container[2]).MoveFigure(1, 0);
    DelElements(container);
    //vector now must be paralelogram (1,0)
    type_name = typeid(*container[0]).name();
    assert(type_name == "12paralelogram");
    assert(container.size() == 1);
}