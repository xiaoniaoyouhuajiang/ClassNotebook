#include <iostream>
#include <cstdlib>  //rand,srand
#include <ctime>
#include "testing.hpp"
#include "algorithms.hpp"

int main() {
	size_t N, pos1, pos2;
	std::cout << "Enter the number of shapes and range:" << std::endl;
	std::cin >> N >> pos1 >> pos2;
    Test(N, pos1 + 1, pos2 + 1);
    std::cout << "Testing is successful" << std::endl;
    return 0;
}