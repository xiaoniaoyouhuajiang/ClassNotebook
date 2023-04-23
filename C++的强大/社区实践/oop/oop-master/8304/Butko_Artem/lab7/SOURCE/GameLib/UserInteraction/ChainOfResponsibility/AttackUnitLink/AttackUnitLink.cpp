//
// Created by Artem Butko on 20/05/2020.
//

#include "AttackUnitLink.h"

void AttackUnitLink::chain(std::string command, std::string player)
{
    if (command == "/attack")
    {
        while (true)
        {
            try
            {
                ICommand* Command = new AttackUnitCommand(field, player);
                Command->Command();
                break;
            }
            catch (LogicalError error)
            {
                std::cout << error.what() << std::endl;
            }
            catch (OutOfRangeError error)
            {
                std::cout << error.what() << std::endl;
            }
            catch (TypeError error)
            {
                std::cout << error.what() << std::endl;
            }
        }
    }
    else Chain::chain(command, player);
}
