#pragma once
#define _CRT_SECURE_NO_WARNINGS//?
#include <iostream>//?

class landscape {
protected:
	int premission_to_pass = 1;
	char unit_to_ban[100] = "\0";
public:
	int i, j;//расположение ландшафта

};

class nettle :public landscape {


public:
	nettle() {

		strcpy(unit_to_ban, "Лучники");

	}


};

class mountain :public landscape {

public:
	mountain() {

		strcpy(unit_to_ban, "Конница");
	}

};

class swamp :public landscape {//болото

public:
	swamp() {

		premission_to_pass = 0;//запрет на проход
	}
};

class flat :public landscape {//равнина

public:
	flat() {
		premission_to_pass = 1;
	}
};

class inert_obj {
protected:
	char name[100];
	int i, j;
public:
	int get_i() {

		return i;

	}
	int get_j() {

		return j;
	}
};


class dirt :public inert_obj {

public:
	void operator+(cell& ob) {


		strcpy(name, ob.get_type());


	}

	char* get_name() {
		return name;
	}
};
