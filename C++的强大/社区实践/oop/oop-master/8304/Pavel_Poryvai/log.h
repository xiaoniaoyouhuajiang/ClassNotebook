#pragma once

#include<iostream>
#include <fstream> 
#include"playing_field.h"
#include"pattern_command.h"
#include<vector>
#include <string>
using namespace std;


class Interface_logs {
public:
	virtual void print_action(int id_action) {

	}
};


class Service :public Interface_logs {
public:
	void print_action(int id_action) {


		if (id_action == 1) {

			std::cout << "\nЗапись лога в файл\n";
		}
		else if (id_action == 2) {

			std::cout << "\nВывод лога на дисплей\n";
		}
		else if(id_action == 3) {

			std::cout << "\nБез лога\n";
		}
	}
};

class file_log :public Interface_logs {

	Service RealService;
public:
	virtual void print_action(int id_action) {

		ofstream file; // создаем объект класса ifstream
		file.open("log.txt"); // открываем файл
		RealService.print_action(id_action);


		std::cout << "\nВведите размер поля\n";
		int a, b;
		std::cin >> a >> b;

		int** landscape = new int* [a];
		for (int i = 0; i < a; i++)
			landscape[i] = new int[b];
		for (int i = 0; i < a; i++)
			for (int j = 0; j < b; j++)
				landscape[i][j] = 0;

		playing_field p_f(a, b, landscape);

		file << "\nПоле размера " << a << " " << b <<" Создано"<< "\n";
		std::cout << "\nВведите строку/столбец, куда разместить базу\n";


		int i, j;
		cin >> i >> j;
		p_f.set_base(i, j);


		file << "\nСтрока/столбец, базы " << i <<" "<< j << "\n";

		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";


		int i_base, j_base, i_unit, j_unit;
		cin >> i_base >> j_base >> i_unit >> j_unit;
		p_f.create_unit_of_base(i_base, j_base, i_unit, j_unit);


		file << "\nСтрока/столбец, базы, которая создала юнит, строка/столбец юнита " << i_base <<" "<< j_base <<" "<< i_unit << " "<<j_unit << "\n";

		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";



		cin >> i_base >> j_base >> i_unit >> j_unit;
		p_f.create_unit_of_base(i_base, j_base, i_unit, j_unit);



		file << "\nСтрока/столбец, базы, которая создала юнит, строка/столбец юнита " << i_base << " " << j_base << " " << i_unit << " " << j_unit << "\n";

		std::cout << "\nПередвинуть юнит куда i j/откуда i j \n"; //move(i1, j1, i2, j2);
		int i1, j1, i2, j2;
		cin >> i1 >> j1 >> i2 >> j2;
		p_f.move(i1, j1, i2, j2);

		file << "\nЮнит перешел с i1 j1 на i2 j2 " << i2 <<" "<< j2<<" " << i1<<" " << j1 << "\n";

		




	}

};




class display_log :public Interface_logs {


	Service RealService;
public:
	virtual void print_action(int id_action) {


		RealService.print_action(id_action);

		vector<string> strings;
		string str;
		std::cout << "\nВведите размер поля\n";
		int a, b;
		std::cin >> a >> b;

		int** landscape = new int* [a];
		for (int i = 0; i < a; i++)
			landscape[i] = new int[b];
		for (int i = 0; i < a; i++)
			for (int j = 0; j < b; j++)
				landscape[i][j] = 0;
	
		playing_field p_f(a, b, landscape);
		str =  "\nПоле размера " + std::to_string(a) + " " + std::to_string(b) + " Создано" + "\n";
		strings.push_back(str);
		
		std::cout << "\nВведите строку/столбец, куда разместить базу\n";


		int i, j;
		cin >> i >> j;
		p_f.set_base(i, j);


		str =   "\nСтрока/столбец, базы " + std::to_string(i) + " " + std::to_string(j) + "\n";
		strings.push_back(str);

		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";


		int i_base, j_base, i_unit, j_unit;
		cin >> i_base >> j_base >> i_unit >> j_unit;
		p_f.create_unit_of_base(i_base, j_base, i_unit, j_unit);


		str =  "\nСтрока/столбец, базы, которая создала юнит, строка/столбец юнита " +std::to_string(i_base) +" "+std::to_string(j_base) +" "+ std::to_string(i_unit) +" "+ std::to_string(j_unit) + "\n";
		strings.push_back(str);


		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";



		cin >> i_base >> j_base >> i_unit >> j_unit;
		p_f.create_unit_of_base(i_base, j_base, i_unit, j_unit);

		str = "\nСтрока/столбец, базы, которая создала юнит, строка/столбец юнита " + std::to_string(i_base) + " " + std::to_string(j_base) + " " + std::to_string(i_unit) + " " + std::to_string(j_unit) + "\n";
		strings.push_back(str);

		std::cout << "\nПередвинуть юнит куда i j/откуда i j \n"; //move(i1, j1, i2, j2);
		int i1, j1, i2, j2;
		cin >> i1 >> j1 >> i2 >> j2;
		p_f.move(i1, j1, i2, j2);

		str =  "\nЮнит перешел с i1 j1 на i2 j2 " +std::to_string( i2) +" "+ std::to_string(j2) +" "+ std::to_string(i1) +" "+ std::to_string(j1) + "\n";
		strings.push_back(str);


		for (int i = 0; i < strings.size(); i++)
			std::cout << strings[i];
	




	}


};



class no_log :public Interface_logs {


	Service RealService;
public:
	virtual void print_action(int id_action) {


		std::cout << "\nВведите размер поля\n";
		int a, b;
		std::cin >> a >> b;

		int** landscape = new int* [a];
		for (int i = 0; i < a; i++)
			landscape[i] = new int[b];
		for (int i = 0; i < a; i++)
			for (int j = 0; j < b; j++)
				landscape[i][j] = 0;

		playing_field p_f(a, b, landscape);

		std::cout << "\nВведите строку/столбец, куда разместить базу\n";


		int i, j;
		cin >> i >> j;
		p_f.set_base(i, j);


		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";


		int i_base, j_base, i_unit, j_unit;
		cin >> i_base >> j_base >> i_unit >> j_unit;
		p_f.create_unit_of_base(i_base, j_base, i_unit, j_unit);


		std::cout << "\nВведите строку/столбец, базы, которая создает юнит,строку/столбец куда разместить юнит\n";


		cin >> i_base >> j_base >> i_unit >> j_unit;
		p_f.create_unit_of_base(i_base, j_base, i_unit, j_unit);


		std::cout << "\nПередвинуть юнит куда i j/откуда i j \n"; //move(i1, j1, i2, j2);
		int i1, j1, i2, j2;
		cin >> i1 >> j1 >> i2 >> j2;
		p_f.move(i1, j1, i2, j2);




	}
};

