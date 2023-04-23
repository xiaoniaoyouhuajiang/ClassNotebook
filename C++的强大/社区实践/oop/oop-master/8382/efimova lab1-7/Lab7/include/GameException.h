#pragma once
#include <exception>
class GameException : public std::exception //наше игровое искл. наследуется от станд. исключения
{
	const char* _file; //имя файла, в котор. произошла ошибка
	int _line; //линия в коде
	const char* _func; // имя ф-ции
	const char* _info; // доп. инфа

public: // конструктор, принимающий данные об ошибке
	GameException(const char* msg, const char* file, int line, const char* func, const char* info = "") : std::exception(msg),
		_file(file),// он принимает имя файла и тд
		_line(line),
		_func(func),
		_info(info)//мб пустой
	{
	}
	// 4 геттера, получ. информацию
	const char* getFile() const { return _file; }
	int getLine() const { return _line; }
	const char* getFunc() const { return _func; }
	const char* getInfo() const { return _info; }
};

