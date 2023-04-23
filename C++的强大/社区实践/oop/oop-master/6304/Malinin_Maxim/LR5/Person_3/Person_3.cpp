// Person_3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>

#include "Paint.h"
#include "Card.h"
#include "Deck.h"


#include <Windows.h>
#include <iostream>




int main()
{
	Paint Mypaint;
	//Mypaint.fill_box("=", 3, 50, 15, 20, 30);
	//Mypaint.print_text("-----------------\n|               |\n|{s(10, 0)} hello\tWorld {s(15, 0)}|\n|               |\n-----------------\n", 30, 20);
	//std::cout << "\n" << Mypaint.Width_box("----------------------------\n|               |\n\n|{s(10, 0)} hello\tWorld {s(15, 0)}|\n|               |\n-----------------\n") << "\n";
	//Mypaint.print_Hline(5, 5, 15, 20);
	//Mypaint.print_Wline(5, 6, 15, 10);
	//Mypaint.print_box(10, 10, 30, 20, 12);
	//Mypaint.setcur(50, 50);
	//Mypaint.loading(10, 1000, 20, 20);

	//Card myCard(5);
	//std::cout << myCard.Card_to_filestring();
	//std::cout << "\n\n";
	//myCard.recard((std::string)"Maskit", 5, 5, 5555, 34, 12, 3, 3,(std::string)"deadas");
	//std::cout << "\n\n";
	//std::cout << myCard.Card_to_printstring();
	//std::cout << "\n\n";
	//myCard.character_up(*myCard.int_to_Character(4), 10);
	//myCard.character_up(*myCard.int_to_Character(3), -10);
	//Mypaint.print_text(myCard.Card_to_printstring(), 35, 0);


	//std::cout << myCard.Card_to_filestring();
	//std::cout << "\n\n";
	//std::cout << "1   | asd           | 0   | 5   | 1   | 5555| 34  | 12  | goblin  | water   | it`s better card!| ";
	//std::cout << "\n\n";

	//myCard.filestring_to_Card("1   | asd           | 0   | 5   | 1   | 5555| 34  | 12  | goblin  | water   | it`s better card!| ");
	//std::cout << "\n\n";	
	//std::cout << myCard.Card_to_filestring();
	//std::cout << "\n\n";


	//system("pause");
	Deck mydeck;
	mydeck.new_card();
	mydeck.new_card();
	mydeck.new_card();
	mydeck.new_card();
	mydeck.new_card();

	mydeck[0].recard((std::string)"qwe", 5, 1, 5555, 34, 12, 3, 3, (std::string)"deadas");
	mydeck[1].recard((std::string)"asd", 1, 2, 5555, 34, 12, 3, 3, (std::string)"it`s better card!");
	mydeck[2].recard((std::string)"zxc zxc", 2, 3, 5555, 34, 12, 3, 3, (std::string)"deadas");
	mydeck[3].recard((std::string)"Maskit", 3, 4, 5555, 34, 12, 3, 3, (std::string)"deadas");
	mydeck[4].recard((std::string)"sir", 2, 2, 35, 3, 7, 2, 1, (std::string)"last card");


	//Mypaint.print_deck(mydeck, 5, 1, 15, 15);

	Mypaint.deck_menu(mydeck);
	//Mypaint.setcur(0, 31);
	//Mypaint._print_deck(mydeck, 1, 10, 10);
	//std::cout << "-----------------\n|               |\n|{s(10, 0)} hello\tWorld {s(15, 0)}|\n|               |\n-----------------\n";
	//std::cout << Mypaint.text_without_funcs("123{4}{000}5678") << "\n\n";
	//std::cout << Mypaint.text_without_funcs_and_break("12\n34{00\t0}56\n7\t8");
	//Mypaint.print_text("12\n 34{00\t0} 5678907890\n7\t8", 10, 5, 10);
	//system("pause");
	return 0;
}

