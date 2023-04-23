#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

#include "Deck.h"
#include "Card.h"
#include "Fighting_card.h"

class Paint
{
	enum ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

public:
	Paint();
	~Paint();


	void setcur(int x, int y);															//Переводит курсор на позицию (х, у)
	void SetColor(int text, int background);											//Изменяет цвет экрана и текста

	bool isNumber(std::string str);														//Проверяет, является ли строка числом
	int Width_box(std::string str);														//Возвращает максимальную длину строки
	std::string text_without_funcs(std::string str);									//Возвращает текст без функций изменения цвета
	std::string text_without_funcs_and_break(std::string str);							//Возвращает текст без функций изменения цвета и символов перевода строки и табуляции
	void print_text(std::string str, int x, int y);										//Выводит текст с отступом х,у
	void print_text(std::string str, int x, int y, int lenght);							//Выводит текст с отступом х,у и максимальной длиной строки lenght
	void loading(int n, int delay, int x, int y);										//Визуальня картинка загрузки
	void fill_box(int x1, int y1, int x2, int y2);										//Очищает прямоугольник экрна {(x1, y1)(x2, y2)}
	void fill_box(std::string str, int x1, int y1, int x2, int y2);						//Заполняет прямоугольник экрана строками
	void fill_box(std::string str, int width, int x1, int y1, int x2, int y2);			//Рисует полый прямоугольник с шириной стороны widght * str.size()
	void print_Hline(int x, int y, int lenght);											//Рисует горизонтальную линию символами "-"
	void print_Hline(int x, int y, int background, int lenght);							//Рисует горизонтальную линию цветом background
	void print_Wline(int x, int y, int lenght);											//Рисует вертикальную линию символами "|"
	void print_Wline(int x, int y, int background, int lenght);							//Рисует вертикальную линию цветом background
	void print_box(int x1, int y1, int x2, int y2, int background);						//Рисует полый квадрат цветом background

	void screen_info(int &width, int &height);											//Изменияет значения на ширину и высоту экрана
	void deck_menu(Deck &deck);															//Главное меню программы с функционалом(конструктор)

	void reCard(Card &card);															//Изменение значений карты вручную
	void reCard(Card &card, int x, int y);												//Изменение значений карты вручную с записью в (х,у)

	void print_card(Card card, int x, int y);											//Рисует карту в (х,у)
	void print_deck(Deck deck);															//Выводит на экран все карты списком
	void print_deck(Deck deck, int x_indent, int y_indent, int x_field, int y_field);	//Выводит на экран все карты списком с отступами
	void _print_deck(Deck deck, int current, int x, int y);								//Вывод на экран колоды 
	void print_list_deck(Deck deck, int x, int y);										//Вывод на экран списка имен карт
	void print_list_deck(Deck deck, int current, int x, int y);							//Вывод на экран списка имен карт с записью в (х,у)

	void print_fighting_card(Fighting_card fighting_deck, int x_indent, int y_indent);	//Вывод карты на игровом поле

};

