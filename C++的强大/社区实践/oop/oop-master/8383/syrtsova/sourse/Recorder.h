#pragma once
#include <string>
#include <iostream>
#include <fstream>

/// Класс записи

/**
* Адаптируемый класс, содержит функции вывода в терминал и в файл
*/

class Recorder
{
public:
	/// Поток вывода
	std::ofstream out;
	/// Конструктор класса записи
	Recorder();
	/// Деструктор класса записи 
	~Recorder();
	/// Перегруженный оператор вывода в поток
	friend std::ostream& operator << (std::ostream& out, std::string str);
	/// Функция записи в файл
	bool writeToFile(std::string str);
	/// Функция записи в терминал
	bool writeToTerminal(std::string str);
};