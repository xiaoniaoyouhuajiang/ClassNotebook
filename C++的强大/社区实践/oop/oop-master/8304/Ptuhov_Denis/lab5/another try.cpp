#include "UnitFactory.h"  
#include "Field.h"
#include "Dialog.h"
#include <ctime>

int main()
{
	srand(time(nullptr));

	Dialog d;
	d.speak();

	return 0;
}
