#include <iostream>
#include <memory>
#include <vector>

#include "PplayGameTem.hpp"

int main() {
    
    int rule;
    int numPlayers;
    std::shared_ptr<Rules> gameRules;
    
    std::cout << "******** RULES ********" << std::endl;
    std::cout << "RULE 1\n";
    std::cout << "   wining condition - destruction of base\n";
    std::cout << "   5 Units allowed per base\n";
    std::cout << "   player1 starts first\n";
    
    std::cout << "RULE 2\n";
    std::cout << "   wining condition - destruction of base or dead units equals 5 \n";
    std::cout << "   3 Units allowed per base\n";
    std::cout << "   player2 or computer starts first\n";
    
    std::cout << "Input type of rule 1  or 2 : ";
    std::cin >> rule;
    std::cout << "Enter number of players 1(with computer)  or 2 : ";
    
   if (rule == 1)
    {
        gameRules = std::make_shared<Rule1>();
        std::cin  >>  numPlayers;
        if (numPlayers == 1)
        {
            PlayGameTemplate<std::shared_ptr<Rules>, 1> gameTemp(gameRules);
            gameTemp.startGame();
        }
        else if (numPlayers == 2)
        {
           PlayGameTemplate<std::shared_ptr<Rules>, 2> gameTemp(gameRules);
            gameTemp.startGame();
        }
        else return 0;
    }
    else
    {
        gameRules = std::make_shared<Rule2>();
        std::cin  >>  numPlayers;
        if (numPlayers == 1)
        {
           PlayGameTemplate<std::shared_ptr<Rules>, 1> gameTemp(gameRules);
            gameTemp.startGame();
        }
        else if (numPlayers == 2)
        {
           PlayGameTemplate<std::shared_ptr<Rules>, 2> gameTemp(gameRules);
            gameTemp.startGame();
        }
        else return 0;
    }
    
    return 0;
}
