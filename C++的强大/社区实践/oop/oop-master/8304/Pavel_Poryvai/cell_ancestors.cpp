#include"cell_ancestors.h"

cell::cell(const cell& ob) {

	type = new char[50];
	kind = new char[50];
	strcpy(type, ob.type);
	strcpy(kind, ob.kind);


	std::cout << "\nКонструктор копии клетки\n";

	if (strcmp(type, "Пехота") == 0) {

		strcpy(e_weapon_foot, "деревянная палка");//надо?
		health = 20;
		attack_force = 20;
		paracetomol = 10;
	}
	else if (strcmp(type, "Лучники") == 0) {

		strcpy(e_weapon_luchniki, "камешек");
		health = 5;
		attack_force = 10;
		paracetomol = 15;

	}
	else if (strcmp(type, "Конница") == 0) {

		strcpy(e_weapon_konnica, "голова грифона");

		health = 15;
		attack_force = 30;
		paracetomol = 5;

	}

}



void cell::set(const char* type_s, const char* kind_s) {

	type = new char[50];
	kind = new char[50];

	strcpy(type, type_s);//Перепроверить как эта функция работает сделать через strlen
	strcpy(kind, kind_s);

	if (strcmp(type, "Пехота") == 0) {

		strcpy(e_weapon_foot, "деревянная палка");//граница копирования
		health = 20;
		attack_force = 20;
		paracetomol = 10;

	}
	else if (strcmp(type, "Лучники") == 0) {

		strcpy(e_weapon_luchniki, "камешек");
		health = 5;
		attack_force = 10;
		paracetomol = 15;

	}
	else if (strcmp(type, "Конница") == 0) {

		strcpy(e_weapon_konnica, "голова грифона");

		health = 15;
		attack_force = 30;
		paracetomol = 5;

	}


	if (strcmp(type, "Пустая клетка") != 0)
		write_in = 1;


}


cell cell::operator=(const cell& ob) {

	std::cout << "\n Перегрузка оператора = \n";
	if (type != nullptr) {


		if(type != NULL)
			delete type;

		type = new char[50];


		delete kind;
		kind = new char[50];




	}
	else {
		type = new char[50];
		kind = new char[50];
	}

	//	std::cout <<"\n"<< ob.type<<"\n";
	//	std::cout << "\n" << type << "\n";

	strcpy(type, ob.type);
	strcpy(kind, ob.kind);


	if (strcmp(type, "Пехота") == 0) {

		strcpy(e_weapon_foot, "деревянная палка");
		health = 20;
		attack_force = 20;
		paracetomol = 10;
	}
	else if (strcmp(type, "Лучники") == 0) {

		strcpy(e_weapon_luchniki, "камешек");
		health = 5;
		attack_force = 10;
		paracetomol = 15;

	}
	else if (strcmp(type, "Конница") == 0) {

		strcpy(e_weapon_konnica, "голова грифона");

		health = 15;
		attack_force = 30;
		paracetomol = 5;

	}


	if (strcmp(type, "Пустая клетка") != 0)
		write_in = 1;

	return *this;

}


cell init() {


	std::cout << "\nВызвана функция init()\n";
	cell ob;
	char type[50] = "";
	char kind[50] = "";

	std::cout << "Введите тип\n";
	std::cin >> type;
	//std::cout << "Введите вид\n";
	//std::cin >> kind;
	strcpy(kind, "Стандартный");//пока так
	ob.set(type, kind);


	return ob;//Здесь вызывается консруктор копии

}
