#pragma once

class Landscape { //абстрактный класс
protected:
	int color;
	int type;
public:
	int getColor();
	int getType();
	virtual int noPassage(int viewUnit) = 0;
	virtual int getNewColor(int viewObject) = 0;
};

class Grass : public Landscape { //виды для красоты - безопасный
private:
	int view;
public:
	Grass(int view);

	int noPassage(int viewUnit) override {
		return 0;			//может наступить любой
	}
	int getView();
	int getNewColor(int viewObject) override{
		if (view == 1) {
			if (viewObject == 1 || viewObject == 2 || viewObject == 10) return 108;//monstr;
			if (viewObject == 3 || viewObject == 4 || viewObject == 11) return 105;//hero
			if (viewObject == 5 || viewObject == 6 || viewObject == 9) return 111;//people
			if (viewObject == 7) return 109;//good resurse
			if (viewObject == 8) return 96; //bad resurse
		}
		else {
			if (viewObject == 1 || viewObject == 2 || viewObject == 10) return 44;//monstr;
			if (viewObject == 3 || viewObject == 4 || viewObject == 11) return 41;//hero
			if (viewObject == 5 || viewObject == 6 || viewObject == 9) return 47;//people
			if (viewObject == 7) return 45;//good resurse
			if (viewObject == 8) return 32; //bad resurse
		}
	}
};

class Lake : public Landscape { //нельзя наступать никому, кроме целителей
public:
	Lake();

	int noPassage(int viewUnit) override {
		if (viewUnit == 3) return 0; 			//пройти может только целитель
		else return 1;
	}

	int getNewColor(int viewObject) override{
		if (viewObject == 1 || viewObject == 2 || viewObject == 10) return 188;//monstr;
		if (viewObject == 3 || viewObject == 4 || viewObject == 11) return 185;//hero
		if (viewObject == 5 || viewObject == 6 || viewObject == 9) return 191;//people
		if (viewObject == 7) return 189;//good resurse
		if (viewObject == 8) return 176; //bad resurse
	}
};

class ritualCircle : public Landscape { 
public:
	ritualCircle();

	int noPassage(int viewUnit) override {  //можно наступать только магам
		if (viewUnit == 4) return 0;
		else return 1;
	}

	int getNewColor(int viewObject) override {
		if (viewObject == 1 || viewObject == 2 || viewObject == 10) return 76;//monstr;
		if (viewObject == 3 || viewObject == 4 || viewObject == 11) return 73;//hero
		if (viewObject == 5 || viewObject == 6 || viewObject == 9) return 79;//people
		if (viewObject == 7) return 77;//good resurse
		if (viewObject == 8) return 64; //bad resurse
	}

};

class Pit : public Landscape {
public:
	Pit();

	int noPassage(int viewUnit) override { 
		return 1;			//никому нельзя наступать
	}

	int getNewColor(int viewObject) override { //????
		if (viewObject == 1 || viewObject == 2 || viewObject == 10) return 12;//monstr;
		if (viewObject == 3 || viewObject == 4 || viewObject == 11) return 9;//hero
		if (viewObject == 5 || viewObject == 6 || viewObject == 9) return 15;//people
		if (viewObject == 7) return 13;//good resurse
		if (viewObject == 8) return 0; //bad resurse
	}

};