#include "my_list.h"

using namespace stepik;

int main()
{
	std:: cout << "Make the list A with default constructor and push back 9 elements.\nList A: ";
	list<int> lst;
	lst.push_back(1);
	for (int i = 2; i < 9; i++)
		lst.push_back(i);
	lst.out();
	std::cout << "Push front to the list A element '10'.\nList A: ";
	lst.push_front(10);
	lst.out();
	std::cout << "Get size of the list A. Size is: ";
	std::cout << lst.size() << std::endl; 
	std::cout << "Pop back from the list A.\nList A: ";
	lst.pop_back();
	lst.out();
	std::cout << "Pop front from the list A.\nList A: "	;
	lst.pop_front();
	lst.out();
	std::cout << "Clear the list A.\nList A: ";
	lst.clear();
	lst.out();
	std::cout << "Push back to the list A 10 elements and make the list B with copy constructor.\nList B: ";
	for (int i = 1; i < 11; i++)
		lst.push_back(i);
	list<int> lst_2(lst);
	lst_2.out();
	std::cout << "Make C and D lists using ivalue and rvalue and assign them list B.\nList C: ";
	list<int>& lst_3 = lst_2;
	lst_3.out();
	list<int> && lst_4 = list<int>(lst_3);
	std::cout << "List D: ";
	lst_4.out();
	std::cout << "Insert to the list D elem '5' to the begin()+2 position.\nList D: ";
	lst_4.insert(lst_4.begin() + 2, 5);
	lst_4.out();
	std::cout << "Erase elem from the list D with position begin()+3.\nList D:";
	lst_4.erase(lst_4.begin() + 3);
	lst_4.out();
}