#pragma once
#include "playing_field.h"

class Command {

public:
	virtual ~Command(){}
	virtual void execute() = 0;
protected:
	Command( playing_field* p ): p_f( p){}
	playing_field* p_f;
};

class inic_cell_Command : public Command
{

public:
	inic_cell_Command( playing_field *p):Command(p){}
	void execute() {


		std::cout << "\nВведите строку/столбец, куда разместить юнит\n";

		
		int i, j;
		cin >> i >> j;
		p_f->inic_cell(i,j);
	}
};

class set_base_Command : public Command
{

public:
	set_base_Command(playing_field* p) :Command(p) {}
	void execute() {


		std::cout << "\nВведите строку/столбец, куда разместить базу\n";


		int i, j;
		cin >> i >> j;
		p_f->set_base(i, j);
	}
};



class create_unit_of_base_Command : public Command
{

public:
	create_unit_of_base_Command(playing_field* p) :Command(p) {}
	void execute() {


		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";


		int i_base, j_base,i_unit,j_unit;
		cin >> i_base >> j_base>>i_unit>>j_unit;
		p_f->create_unit_of_base(i_base , j_base , i_unit , j_unit);
	}


};

class output_field_Command :public Command {

public:
	output_field_Command(playing_field* p) :Command(p) {}
	void execute() {

		p_f->output_field();
	}
};


class move_Command :public Command {

public:
	move_Command(playing_field* p) :Command(p) {}
	void execute() {


		std::cout << "\nПередвинуть юнит куда i j/откуда i j \n"; //move(i1, j1, i2, j2);
		int i1, j1, i2, j2;
		cin >> i1 >> j1 >> i2 >> j2;
		p_f->move(i1, j1, i2, j2);
	}
};



class attack_Command :public Command {

public:
	attack_Command(playing_field* p) :Command(p) {}
	void execute() {//атака юнитом в i1 j1  другого юнита в i2 j2


		std::cout << "\nАтаковать юнитом на i1 j1 юнит, который на i2 j2 \n";
		int i1, j1, i2, j2;
		cin >> i1 >> j1 >> i2 >> j2;
		p_f->attack(i1, j1, i2, j2);
	}
};




class state_base_Command :public Command {

public:
	state_base_Command(playing_field* p) :Command(p) {}
	void execute() {


		std::cout << "\nПроверка состояния базы \nВведите ее нахождение\n";
		int i,j;
		cin >> i>>j;
		p_f->base_state(i, j);
	}
};
