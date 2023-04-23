#include "my_vector.h"

using namespace stepik;

int main()
{
	using std::cout;
	vector<int> a(10);
	cout << "Make the vector A with 10 elements.\nVector A: ";
	a.out();
	cout << "Make the vector B with copy constructor from A. \nVector B: ";
	vector<int> b(a);
	b.out();
	vector<int> c(5);
	c = a;
	cout << "Make the vector C with 5 elements, then C = A. \nVector C: ";
	c.out();
	cout << "Resize the vector A from 10 to 6 elements. \nVector A: ";
	a.resize(6);
	a.out();
	cout << "Resize the vector A from 6 to 12 elements. \nVector A: ";
	a.resize(12);
	a.out();
	cout << "Erase last element from the vector A. \nVector A: ";
	a.erase(a.end());
	a.out();
	cout << "Erase elements from the vector A in [a.begin() + 1, a.end() - 2].\nVector A: ";
	a.erase(a.begin() + 1, a.end() - 2);
	a.out();
	cout << "Insert element to second position into the vector A.\nVector A: ";
	a.insert(a.begin() + 1, 6);
	a.out();
	cout << "Insert elements from the Vector B (b.begin() + 1, b.end() - 1) to the vector A starting with the third position.\nVector A: ";
	a.insert(a.begin() + 2 , b.begin() + 1, b.end() - 1);
	a.out();
	cout << "Push back to vector A.\nVector A: ";
	a.push_back(13);
	a.out();
}
