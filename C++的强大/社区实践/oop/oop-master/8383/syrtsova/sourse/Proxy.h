#pragma once
#include "Recorder.h"

#include "iostream"


/// Прокси

/**
* Реализованный с помощью паттерна "Прокси" для переключения между разным логированием (в файл, в терминал, без логирования).
*/

class Proxy
{
public:
	/// Объект записи
	Recorder* write;
	/// Состояние записи в файл
	bool logToFile;
	/// Состояние записи в терминал
	bool logToTerminal;
	/// Состояние отсутсвия записи
	bool withoutLog;
	/// Конструктор Proxy
	Proxy(Recorder* write, bool logToFile, bool logToTerminal, bool withoutLog);
	/// Провекра корректности записи данных
	bool specificRequest(std::string str);
};