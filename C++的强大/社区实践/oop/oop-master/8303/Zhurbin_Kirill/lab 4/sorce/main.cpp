#include <iostream>
#include "Field.h"
#include "Iterator.h"
#include "Base.h"
#include "Poisen.h"
#include "Potion.h"
#include "DrinkStrong.h"
#include "DrinkStamina.h"
#include "Handler.h"
#include "Facade.h"

int main() {

    Facade* facade = new Facade();
    std::string command;
    facade->createGame();
    while(true){
            std::cin >> command;
            facade->play(command);
    }

    return 0;
}
