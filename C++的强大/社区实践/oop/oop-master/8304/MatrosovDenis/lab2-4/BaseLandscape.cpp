#include "BaseLandscape.h"
#include <iostream>
LandscapeComposite::LandscapeComposite(int x, int y) {
	Landscape = new BaseLandscape*[x];
	for (int i = 0; i < y;i++) {
		Landscape[i] = new BaseLandscape[y];
	}
	X_SIZE = x;
	Y_SIZE = y;
}

LandscapeComposite::LandscapeComposite(const LandscapeComposite& copy) {
	size_t x = copy.X_SIZE;
	size_t y = copy.Y_SIZE;
	Landscape = new BaseLandscape*[x];
	for (int i = 0; i < y;i++) {
		Landscape[i] = new BaseLandscape[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Landscape[i][j] = copy.Landscape[i][j];
		}
	}
	X_SIZE = x;
	Y_SIZE = y;
}

LandscapeComposite::~LandscapeComposite() {
	for (int i = 0; i < X_SIZE;i++) {
		delete Landscape[i];
	}
	delete Landscape;
}

void LandscapeComposite::GenerateLandscape() {
	srand(time(0));
	int res = 0;
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			res = rand() % 4;
			switch (res)
			{
			case 0:
				Landscape[i][j] = Water_obstacle();
				break;
			case 1:
				Landscape[i][j] = Mountain();
				break;
			case 2:
				Landscape[i][j] = Steppes();
				break;
			case 3:
				Landscape[i][j] = Swamp();
				break;
			}
		}
	}
}

void LandscapeComposite::PrintLAndscape() {
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			std::cout << Landscape[i][j].ID() << " ";
		}
		std::cout << std::endl;
	}
}