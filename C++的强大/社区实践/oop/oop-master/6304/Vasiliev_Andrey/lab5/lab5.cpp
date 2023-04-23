#include <iostream>
#include <vector>
#include <functional>


#include "shape.h"
#include "shared.h"
#include "vector.h"
#include "algs.h"
#include <cassert>

typedef stepik::shared_ptr<Shape> shapePointer;

class compare_class {
  public:
  bool operator()(const void* a) {
	return   (  ((shapePointer*)a)->get()->S()>=40   )
		   &&(  ((shapePointer*)a)->get()->S()<=50   );
  }
};


bool no_modify_test(stepik::vector<shapePointer> & vec)
{
	compare_class comp;
	auto e = stepik::findFirst(vec.begin(),vec.end(),comp);
	if(e == vec.end())
		return false;
	return true;
}

bool modify_test(stepik::vector<shapePointer> & vec)
{
	auto e = //Второй диапазон состоит из элементов >= 10
			stepik::divide(vec.begin(),vec.end(),[](const void* a){
		return ((shapePointer*)a)->get()->P()>=10;});

	if(e != vec.end()){

		auto k = //теперь во втором диапазоне ищем < 10 (там их быть не должно)
		stepik::divide(e,vec.end(),[](const void* a){
		return ((shapePointer*)a)->get()->P()<10;});

		if(k== vec.end()) //если элементов нет - возвращаем true
			return true;
		return false;
	}
	return false;

}

int main()
{
	stepik::vector<shapePointer> cont;
	stepik::fillRandomly(cont,10,10);



	stepik::printS(cont);
	cout << "\n";
	stepik::printP(cont);



	{
	cout << "\nLooking for element with area between 40 and 50: \n";
	compare_class func;
	auto e =
	 stepik::findFirst(cont.begin(),cont.end(),func);

	if(e != cont.end())
		cout << ** e;
	}



	{
	cout << "\nModify array, that every elment with perimetr < 15 will be in the end:\n";

	auto e =
			stepik::divide(cont.begin(),cont.end(),[](const void* a){
		return ((shapePointer*)a)->get()->P()<15;});

	stepik::printP(cont);

	cout << "\nFirst figure of second range: \n";
	if(e != cont.end())
		cout << ** e;
	}



	cont.erase(cont.begin(),cont.end());
	stepik::fillRandomly(cont,1000,6);
	if(!no_modify_test(cont))
		cout <<"Element not found and this is right\n";

	if(modify_test(cont))
		cout << "Modified is successfull\n";
	else
		cout << "Not successfull\n";


	return 0;
}
