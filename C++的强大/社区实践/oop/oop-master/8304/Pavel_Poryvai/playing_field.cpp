#include"cell_ancestors.h"
#include"playing_field.h"



void playing_field::move(int i1, int j1, int i2, int j2) {// (далее продумать менять ли,не доработано на конницу, лучников)

	std::cout << "\nВызвана функция move\n";

	if (сard_landscape[i1][j1] != 3 ) {//? для 2

		p_f[i1][j1] = p_f[i2][j2];//вызывается конструктор копии;
		remove_obj(i2, j2);


		//не обновляется база
	}
	else
		std::cout << "\nВ заданной клетке болото, не возможно переместиться сюда\n";

	//remove_obj(i2, j2);

}



void playing_field::remove_obj(int i, int j) {


	std::cout << "\nУдаляем юнит на клетке\n";
	p_f[i][j].remove();
	//не обновляется база
}


playing_field::~playing_field() {


	if (p_f) {

		for (int i = 0; i < height; i++) {

			delete[] p_f[i];//таким образом удаляется массив объектов


		}

		delete p_f;
	}

	std::cout << "Объект поле удален\n";



}






void playing_field::output_field() {//поменять под 2 л





	for (int i = 0; i < height; i++) {


		std::cout << "\n";

		for (int j = 0; j < width; j++) {


			if (p_f[i][j].is_writein() == 1) {

				std::cout << p_f[i][j].get_type();
				std::cout << " ";
			}
			else if (p_f[i][j].is_writein() == 0) {

				std::cout << "Пустая клетка";
				std::cout << " ";


			}
			else if (p_f[i][j].write_in == 2 || p_f[i][j].write_in == 3) {
				std::cout << "База";
				std::cout << " ";
			}


		}

	}

	std::cout << "\n";

}

void playing_field::inic_cell(int i, int j) {

	std::cout << "\nВызвана инициализация клетки\n";

	if (p_f[i][j].write_in == 0) {//Добавить проверку
		p_f[i][j] = init();
		p_f[i][j].write_in = 1;
	}
	else if (p_f[i][j].write_in == 1)
		std::cout << "\nВ клетке юнит\n";
	else if (p_f[i][j].write_in == 2 || p_f[i][j].write_in == 3)
		std::cout << "\nВ клетке база\n";

}





playing_field::playing_field(int height, int width, int** m) {

	this->height = height;
	this->width = width;


	max_obj = height * width;

	p_f = new cell * [height];

	for (int i = 0; i < height; i++) {

		p_f[i] = new cell[width];

	}
	i_mountains = i_swamps = i_nettles = i_flats = 0;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {



			if (m[i][j] == 1) {//крапива
				сard_landscape[i][j] = 1;
				nettles[i_nettles].i = i;
				nettles[i_nettles].j = j;
				i_nettles++;

			}
			else if (m[i][j] == 2) {//гора
				сard_landscape[i][j] = 2;
				mountains[i_mountains].i = i;
				mountains[i_mountains].j = j;
				i_mountains++;
			}
			else if (m[i][j] == 3) {//болото
				сard_landscape[i][j] = 3;
				swamps[i_swamps].i = i;
				swamps[i_swamps].j = j;
				i_swamps++;
			}
			else if (m[i][j] == 0) {//равнина
				сard_landscape[i][j] = 0;
				flats[i_flats].i = i;
				flats[i_flats].j = j;
				i_flats++;

			}
		}
	std::cout << "Поле создано c помощью конструктора с параметрами \n\n";
}


playing_field playing_field::operator=(playing_field& ob) {


	std::cout << "\nВызвана перегрузка оператора = для playing_field\n";

	height = ob.height;
	width = ob.width;
	max_obj = ob.max_obj;

	if (p_f != nullptr) {

		for (int i = 0; i < height; i++)
			delete[] p_f[i];

		delete p_f;

	}

	p_f = new cell * [height];

	for (int i = 0; i < height; i++)
		p_f[i] = new cell[width];






	for (int i = 0; i < height; i++)

		for (int j = 0; j < width; j++) {
			if (ob.p_f[i][j].is_writein() == 1)
				p_f[i][j].set(ob.get_type(i, j), ob.get_kind(i, j));


		}
	//p_f[i][j] = ob.get_cell(i,j);//здесь вызывается перегрузка и конструктор копии cell 

	return *this;
}


playing_field::playing_field(const playing_field& ob) {// для =  он условный

	std::cout << "\nВызван конструктор копии поля\n";

	p_f = new cell * [1];
	p_f[0] = new cell[1];
}

void playing_field::create_unit_of_base(int i_base, int j_base, int i_unit, int j_unit) {//подстроить под landscape

	if (p_f[i_base][j_base].write_in == 2 || p_f[i_base][j_base].write_in == 3) {

		if (p_f[i_unit][j_unit].write_in == 1 || p_f[i_unit][j_unit].write_in == 2 || p_f[i_unit][j_unit].write_in == 3) {

			std::cout << "\nОшибка в данных невозможно разместить юнит здесь\n";
			return;

		}


		if (сard_landscape[i_unit][j_unit] != 3) {

			char string[100] = "\0";

			if (сard_landscape[i_unit][j_unit] == 1)//равнина крапива гора болото
				strcpy(string, "Лучники");

			if (сard_landscape[i_unit][j_unit] == 2)
				strcpy(string, "Коннница");

			else {
				if (strlen(string) > 0) {
					if (p_f[i_base][j_base].create_unit_from_base(i_unit, j_unit) == true) {

						std::cout << "\nВ этой местности нельзя разместить объект " << string << "\n";

						p_f[i_unit][j_unit] = init();

						сard_landscape[i_unit][j_unit] = 1;
						p_f[i_unit][j_unit].write_in = 1;
						std::cout << "\nОт базы инициализирован объект юнит(create_unit_of_base)\n";
					}
					else
						std::cout << "\nБаза не может создать больше юнитов\n";
				}
				else {

					if (p_f[i_base][j_base].create_unit_from_base(i_unit, j_unit) == true) {



						сard_landscape[i_unit][j_unit] = 1;

						p_f[i_unit][j_unit].write_in = 1;
						p_f[i_unit][j_unit] = init();


						std::cout << "\nОт базы инициализирован объект юнит(create_unit_of_base)\n";

					}
					else
						std::cout << "\nБаза не может создать больше юнитов\n";
				}
			}

		}
		else if (сard_landscape[i_unit][j_unit] == 3) {
			std::cout << "В этой клетке болото и ничего нельзя разместить\n";
		}
	}
	else
		std::cout << "\nОшибка в данных, базы в указанной клетке нет\n";



}//надо как то связать юнит с базой


void playing_field::attack(int i1, int j1, int i2, int j2) {//атака юнитом в i1 j1  другого юнита в i2 j2
	
	if (p_f[i1][j1].write_in != 1 ) {
		std::cout << "\nВ 1 клетке нет, атакующего юнита\n";
	}
	else {

		if (p_f[i2][j2].write_in != 1) {

			std::cout << "\nКлетка пуста или в ней база, атака невозможна\n";
		}
		else {

			int a, b;
			int health = p_f[i2][j2].get_health() - p_f[i1][j1].get_attack_force();

			if (health <= 0) {

				p_f[i2][j2].remove();

				if (strcmp(p_f[i1][j1].get_type(), "Лучники") != 0) {
					move(i2, j2, i1, j1);

					//если юнит от базы убрать его из списка в базе

					for (int k = 0; k < 100; k++) {

						if (bases[k].i != -1) {

							units_location* p = p_f[bases[k].i][bases[k].j].get_units_location();


							for (int i = 0; i < p_f[bases[k].i][bases[k].j].get_number_of_units(); i++)
								if (p[i].i == i2 && p[i].j == j2) {
									p[i].i = -1;
									p[i].j = -1;//не лучников обновляем в списке базы
									a = i2;
									b = j2;
								}


							for (int i = 0; i < p_f[bases[k].i][bases[k].j].get_number_of_units(); i++)
								if (p[i].i == i1 && p[i].j == j1) {
									p[i].i = a;
									p[i].j = b;//не лучников обновляем в списке базы
								}

							


						}
					}

				}
				//надо определить 
			}//можно добавить else и отнять здоровье

		}

	}

};


void playing_field::base_state(int i, int j) {


	if (p_f[i][j].write_in == 2 || p_f[i][j].write_in == 3) {

		p_f[i][j].display_units(i, j);

		
	}
	else {

		std::cout << "\nНа данной клетке нет базы\n";
	
	}

}
