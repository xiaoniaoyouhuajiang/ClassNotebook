#include"playing_field.h"
#include"example_Composite.h"
#include"pattern_command.h"
#include"log.h"
#include<vector>




void Client(Interface_logs* Log,int a) {

	
	Log->print_action(a);
	
}
int main()
{
	//lw4
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	

	std::cout << "\nЛог вывести в файл или записать на экране,без лога?(1/2/3) \n";
	int a;
	cin >> a;

	if (a == 1) {

		Client(new file_log, 1);
	}
	else if (a == 2) {

		Client(new display_log, 2);
	}

	else if (a == 3) {

		Client(new no_log, 3);
	}


	return 0;
}

