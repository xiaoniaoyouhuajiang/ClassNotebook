#include <iostream>
//#include "facade.h"
#include "game.h"

Game<Rule1, 2>* Game<Rule1, 2>::game = nullptr;
Game<Rule1, 3>* Game<Rule1, 3>::game = nullptr;
Game<Rule2, 2>* Game<Rule2, 2>::game = nullptr;
Game<Rule2, 3>* Game<Rule2, 3>::game = nullptr;

using namespace std;

int main()
{
    //Facade* facade = new Facade;
    //facade->prepareGame();

    cout << "Choose rules for game\n1) Rule 1\n2) Rule 2\n";
    string ruleStr;
    getline(cin, ruleStr);

    while(true){
        if (ruleStr == "1" || ruleStr == "2")
            break;
        else{
            cout << "Incorrect rule. Choose again: ";
            getline(cin, ruleStr);
        }
    }

    cout << "Enter number of players (can be 2 or 3): ";
    string players;
    getline(cin, players);

    while(true){
        if (players == "2" || players == "3")
            break;
        else{
            cout << "Incorrect number. Enter again: ";
            getline(cin, players);
        }
    }

    if (ruleStr == "1"){
        if (players == "2"){
            Game <Rule1, 2> *game = Game<Rule1, 2>::getGame();
            game->startGame();
        }
        else {
            Game <Rule1, 3> *game = Game<Rule1, 3>::getGame();
            game->startGame();
        }
    }
    else{
        if (players == "2"){
            Game <Rule2, 2> *game = Game<Rule2, 2>::getGame();
            game->startGame();
        }
        else {
            Game <Rule2, 3> *game = Game<Rule2, 3>::getGame();
            game->startGame();
        }
    }

    return 0;
}
