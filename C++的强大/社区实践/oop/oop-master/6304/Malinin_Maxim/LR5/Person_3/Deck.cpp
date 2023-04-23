#include "stdafx.h"
#include "Deck.h"


Card& Deck::operator[](int pos) {
	return (*this).deck[pos];
}

Deck& Deck::operator=(Deck deck1) {
	deck.clear();
	for (int i = 0; i < deck1.deck_size(); ++i) {
		(*this).deck.push_back(deck1[i]);
	}
	return *this;
}

Deck::Deck() : deck({})
{
}

Deck::Deck(std::string filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open()) {								// если файл не открыт
		std::cout << "File not founded!\n";	// сообщить об этом
		return;
	}
	else
	{
		while (!fin.eof()) {
			char ch[120];
			fin.getline(ch, 120);
			filename = ch;
			deck.push_back(Card(deck.size()));
			deck[deck.size() - 1].filestring_to_Card(filename);
		}
	}
	fin.close();
}

Deck::~Deck()
{
}

void Deck::new_card() {
	deck.push_back(Card(deck.size()));
}

void Deck::delete_card(int current) {
	deck.erase(deck.begin() + current);
	std::vector<Card>(deck).swap(deck);
}

int Deck::deck_size() {
	return deck.size();
}

void Deck::shuffle() {
	std::random_shuffle(deck.begin(), deck.end());
}

void Deck::restore_order() {
	std::sort(deck.begin(), deck.end());
}

std::string Deck::deck_to_filestring() {
	std::string filestring = "";
	for (int i = 0; i < deck.size(); ++i) {
		filestring += deck[i].Card_to_filestring() + "\n";
	}
	return filestring.substr(0, filestring.size() - 1);
}

void Deck::filestring_to_deck(std::string filestring) {
	int n = 0;
	int size = 0;
	while (size != filestring.size()) {
		size = filestring.find("\n", n);
		if (size == -1) { break; }
		new_card();
		deck[deck.size() - 1].filestring_to_Card(filestring.substr(n, size - n));
		deck[deck.size() - 1].setID(deck.size() - 1);
		n = size + 1;
	}
}

void Deck::deck_to_file(std::string filename) {
	std::string filestring = "";
	std::ofstream fout(filename);
	fout.clear();
	fout << deck_to_filestring();
	fout.close();
}

void Deck::file_to_deck(std::string filename) {
	std::string file_str;
	std::ifstream fin(filename);
	if (!fin.is_open()) { // если файл не открыт
		std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
		return;
	}
	else
	{
		while (!fin.eof()) {
			char ch[120];
			
			fin.getline(ch, 120);
			if (ch != "\0") {
				file_str += ch;
				file_str += "\n";
			}
		}
		//std::cout << "=====\n" << file_str << " =====\n";
		filestring_to_deck(file_str);
	}
	fin.close();
}