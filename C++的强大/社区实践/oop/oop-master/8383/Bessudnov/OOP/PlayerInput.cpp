#include "pch.h"
#include "PlayerInput.h"
#include "GameField.h"
#include "GameUnits.h"
#include "GameUtilities.h"


PlayerInput::PlayerInput() {

}

PlayerInput::~PlayerInput() {
}

Vector2D PlayerInput::readMapDimensions() {
	Vector2D nDims;
	std::cout << "Enter new map length: ";
	std::cin >> nDims.x;
	std::cout << "Enter new map heigth: ";
	std::cin >> nDims.y;
	return nDims;
}

std::string PlayerInput::readString(std::string messege) {
	std::string fileName;
	std::cout << messege;
	std::cin >> fileName;

	return fileName;
}

void PlayerInput::readInput(char &messageCode) {
	std::cout << "Enter command: ";
	std::cin >> messageCode;
}

