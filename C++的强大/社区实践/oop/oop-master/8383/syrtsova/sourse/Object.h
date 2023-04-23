#pragma once

///Класс объекта
class Object {
public:
	enum colorLand
	{
		black,
		blue,
		green,
		cyan,
		red,
		purple,
		yellow,
		white,
		grey,
		lightBlue,
		lightGreen,
		lightCyan,
		lightRed
	};
	char object;
	int color = colorLand::white;
	Object(char obj) :object(obj) {};
	Object() :object('X') {};
};
