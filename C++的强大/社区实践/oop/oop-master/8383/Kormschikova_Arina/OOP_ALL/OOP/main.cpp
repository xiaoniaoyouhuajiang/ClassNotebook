
#include "Game.h"
#include "Rules.h"
#include "Exeptions.h"
#include <exception>
std::string logsName;


int main(int argc, const char * argv[]) {
    std::time_t t = std::time(NULL);
    char s[9];
    std::strftime(s, 9, "%T", std::localtime(&t));
    logsName = logsName + "Logs"+s+".txt";
    int input = 0;
    std::cin.exceptions(std::istream::badbit| std::istream::failbit);
    Game<RuleBattleBetweenTeams>* game;
    Game<RuleSurvival>* game2;
    std::cout<<"Enter the mode of game: 1 -  survive (one player, without base) 2 - battle between teams (with base (1-2 players))"<<std::endl;
    
    try{
        std::cin>>input;
    }
    catch(const std::istream::failure& ex){
        std::cout<<"Wrong input!"<<std::endl;
        ex.code();
        ex.what();
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        input = 2;
    }
    
    switch (input) {
        case 1:
            game2 = Game<RuleSurvival>::getInctance();
            while (1) {
                game2->start(SECONDRULE);
                input = 0;
                std::cout<<"Would you like to start a new game? 1 - yes, 2 - no (default)"<<std::endl;
                
                try{
                    std::cin>>input;
                }
                catch(const std::istream::failure& ex){
                    ex.code();
                    ex.what();
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    input = 2;
                }
                
                switch (input) {
                    case 1:
                        continue;
                    case 2:
                    default:
                        return 0;
                        break;
                }
            }
            break;
        case 2:
            game = Game<RuleBattleBetweenTeams>::getInctance();
            input = 0;
            while(1){
                std::cout<<"Enter the number of players (1-2) 2 - default"<<std::endl;
                
                try{
                    std::cin>>input;
                }
                catch(const std::istream::failure& ex){
                    ex.code();
                    ex.what();
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    input = 2;
                }
                
                switch (input) {
                    case 1:
                        game->start(ONEPLAYER);
                        break;
                    case 2:
                    default:

                        game->start(TWOPLAYERS);
                        break;
                }
                std::cout<<"Would you like to start a new game? 1 - yes, 2 - no (default)"<<std::endl;
                try{
                    std::cin>>input;
                }
                catch(const std::istream::failure& ex){
                    ex.code();
                    ex.what();
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    input = 2;
                }
                
                switch (input) {
                    case 1:
                        continue;
                    case 2:
                    default:
                        return 0;
                        break;
                }
            }
            break;
        default:
            break;
    }

    

     return 0;
}


