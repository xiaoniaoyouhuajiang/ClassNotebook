#include "BoardBuilder.h"

GameBoard* BoardBuilder::createBoard() {
	int length;
	int width;
	std::cout << "Enter board length and width" << std::endl;
	std::cin >> length;
	std::cin >> width;
	while (length > 30 || length < 10 || width > 30 || width < 10) {
		std::cerr << "Error with board size" << std::endl;
		std::cout << "Enter board length and width" << std::endl;
		std::cin >> length;
		std::cin >> width;
	}
	
	return new GameBoard(length, width);
}

GameBoard* BoardBuilder::createBoard(int length, int width)
{
	return new GameBoard(length, width);
}

void BoardBuilder::printBoard(GameBoard* board) {

	for (int i = 0; i < board->getLength(); i++) {
		if (i < 10) std::cout << i << " |";
		else std::cout << i << "|";
		std::cout << board->getLine(i);
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (int i = 0; i < board->getWidth(); i++)
	{
		if (i + 1 < 10) std::cout << "  " << i << " ";
		else std::cout << "  " << i;
	}
	std::cout << std::endl;
	std::cout << "---";
	for (int i = 0; i < board->getWidth(); i++)
	{
		std::cout << "----";
	}
	std::cout << std::endl;
}

void BoardBuilder::showExamples()
{
	std::cout << "Copy board example" << std::endl;
	GameBoard* board1 = BoardBuilder::createBoard(12, 12);
	BoardBuilder::printBoard(board1);
}
