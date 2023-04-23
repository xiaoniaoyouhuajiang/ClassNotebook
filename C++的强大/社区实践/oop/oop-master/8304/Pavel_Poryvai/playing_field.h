#pragma once
#include"cell_ancestors.h"
#include"landscape_and_inertobj.h"

cell init();//если поместить в playing_field.cpp, что-то изменится?
struct bases_location {

	int i = -1;
	int j = -1;

};


class playing_field {

	int max_obj;
	int height;
	int width;
	cell** p_f;

	bases_location bases[100];
	int i_bases = 0;

	int сard_landscape[100][100];
	mountain mountains[100];
	swamp swamps[100];
	nettle nettles[100];
	flat flats[100];

	int i_mountains, i_swamps, i_nettles, i_flats;

public:


	playing_field(int height, int width, int** m);
	playing_field(const playing_field& ob2);//Конструктор копии


	void remove_obj(int i, int j);
	playing_field() {

		max_obj = 0;
		height = width = 0;
		p_f = nullptr;

		std::cout << "\nОбъект создан с помощью конструктора без параметров\n\n";

	}

	void inic_cell(int i, int j);//клетка

	//лаба 2
	void set_base(int i, int j) {

		p_f[i][j].write_in = 2;//устанавливаем базу

		bases[i_bases] = { i,j };
		сard_landscape[i][j] = 2;
		i_bases++;

	}

	void create_unit_of_base(int i_base, int j_base, int i_unit, int j_unit);//создание юнита от базы
	//end lw2
	//в базе должны быть все расположения юнитов и при их перемещении они должны обновляться

	//Для след функций можно сделать проверку указателя p_f
	char* type_cell(int i, int j) {


		return p_f[i][j].get_type();

	}


	int health_cell(int i, int j) {

		return p_f[i][j].get_health();
	}

	int attack_cell(int i, int j) {

		return p_f[i][j].get_attack_force();

	}

	int drug_cell(int i, int j) {

		return p_f[i][j].get_paracetomol();
	}

	void output_field();
	int get_height() {
		return height;

	}

	int get_width() {

		return width;
	}

	//cell get_cell(int i,int j){

	//	cell ob;
	//	ob = p_f[i][j];

	//	return ob;//конструктор копии?
	//}

	char* get_type(int i, int j) {

		return p_f[i][j].get_type();
	}

	char* get_kind(int i, int j) {
		return p_f[i][j].get_kind();
	}
	void move(int i1, int j, int i2, int j2);

	playing_field operator=(playing_field& ob);

	~playing_field();

	void attack(int i1, int j1, int i2, int j2);//атака юнитом базы или другого юнита
	void base_state(int i, int j);//Подкорректировать

};
