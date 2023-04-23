#include "pch.h"
#include "Landscape.h"
#include "Object.h"
#include "Map.h"
#include "ctime"
#include <Windows.h>


Land::Land(char N, int width, int height, int col) : name(N), width(width), height(height){
		object = name;
		max_size = width*height;
		color = col;
		if (name == '~') max_water = max_size * 0.2;
		else max_water = 0;
		if (name == '*') max_grass = max_size;
		else max_grass = 0;
		if (name == '^') max_stones = max_size * 0.3;
		else max_stones = 0;
}


void Land::generation(Map *field)
{
	srand(time(0));

	while (max_grass != 0)
	{
		x = 1;
		y = 1;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++)
			{
				(*field).addOnMap(x, y, this);
				max_grass--;
				y++;
			}
			x++;
			y = 1;
		}
	}
	while (max_water != 0)
	{
		x = rand() % width;
		y = rand() % height;
		(*field).addOnMap(x, y, this);
		max_water--;
	}
	while (max_stones != 0)
	{
		x = rand() % width;
		y = rand() % height;
		(*field).addOnMap(x, y, this);
		max_stones--; 
	}

}


Water::Water(int width, int height, Map* field) : Land('~', width, height, colorLand::blue) {
	generation(field);
}


Grass::Grass(int width, int height, Map *field) : Land('*', width, height, colorLand::green) {
	generation(field);
}


Stones::Stones(int width, int height, Map *field) : Land('^', width, height, colorLand::grey) {
	generation(field);
}

Landscape::Landscape(int x_max, int y_max, Map* field)
{
	grass = new Grass(x_max, y_max, field);
	stones = new Stones(x_max, y_max, field);
	water = new Water(x_max, y_max, field);
}
