#include"playing_field.h"
#include"example_Composite.h"
#include"pattern_command.h"
#include<vector>
int main()
{
	//lw1
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
		 
	int a, b;
	std::cin >> a >> b;

	int** landscape = new int* [a];
	for (int i = 0; i < a; i++)
		landscape[i] = new int[b];
	for (int i = 0; i < a; i++)
		for (int j = 0; j < b; j++)
			landscape[i][j] = 0;

	playing_field p_f(a, b,landscape);

	vector<Command*> Commands;

	Commands.push_back(new set_base_Command(&p_f));
	Commands.push_back(new create_unit_of_base_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));
	Commands.push_back(new create_unit_of_base_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));
	Commands.push_back(new create_unit_of_base_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));
	Commands.push_back(new state_base_Command(&p_f));
	Commands.push_back(new attack_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));
	Commands.push_back(new attack_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));
	Commands.push_back(new attack_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));
	Commands.push_back(new state_base_Command(&p_f));
	Commands.push_back(new move_Command(&p_f));
	Commands.push_back(new output_field_Command(&p_f));

	for (int i = 0; i < Commands.size(); i++)
		Commands[i]->execute();

	for (int i = 0; i < Commands.size(); i++)
		delete Commands[i];

	
	return 0;
}
