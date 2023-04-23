#include <iostream>
#include "unit_factory.h"
#include "Dialog.h"

int main()
{
	Fasad* fsd = new Fasad;
	MainDialog dlg(fsd);
	dlg.start();
}
