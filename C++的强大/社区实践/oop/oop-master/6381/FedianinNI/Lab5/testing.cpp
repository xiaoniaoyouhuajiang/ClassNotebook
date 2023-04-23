#include "testing.hpp"

void Test(size_t N, size_t pos1, size_t pos2) {
	std::cout << "Test:" << std::endl << "---------------------------" << std::endl;
	std::cout << "Created container with " << N << " figure:" << std::endl;
    my_space::vector<my_space::shared_ptr<Shape>> my_container = FillContainerWithRandShapes(N);
    PrintVectorOfShapes(my_container);
	my_space::vector<my_space::shared_ptr<Shape>> first_group, second_group;// 1 и 2 группы
	PrintInfoAbout(my_container, first_group, second_group, pos1, pos2);
	my_space::vector<my_space::shared_ptr<Shape>> copy_container = Modified(my_container, first_group);
	std::cout << "Modified container: " << std::endl;
	PrintVectorOfShapes(my_container);
}