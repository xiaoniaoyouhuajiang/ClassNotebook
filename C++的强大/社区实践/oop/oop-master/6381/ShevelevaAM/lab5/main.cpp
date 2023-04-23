#include <iostream>
#include <cmath>
#include <assert.h>
#include <algorithm> 
#include <cstddef> 
#include <initializer_list>
#include <stdexcept>
#include "my_vector.h"
#include "my_shared_ptr.h"
#include "sharp.h"
#include "test.h"

int main()
 {
	srand(time(0));
	
	if(test1()) std::cout<<"Тест 1 пройден.\n";	
	else std::cout<<"Тест 1 ОШИБКА.\n";	
	if(test2()) std::cout<<"Тест 2 пройден.\n";	
	else std::cout<<"Тест 2 ОШИБКА.\n";	
	if(test3()) std::cout<<"Тест 3 пройден.\n";	
	else std::cout<<"Тест 3 ОШИБКА.\n";	
	if(test4()) std::cout<<"Тест 4 пройден.\n";	
	else std::cout<<"Тест 4 ОШИБКА.\n";	
	test5();
    return 0;
  }
