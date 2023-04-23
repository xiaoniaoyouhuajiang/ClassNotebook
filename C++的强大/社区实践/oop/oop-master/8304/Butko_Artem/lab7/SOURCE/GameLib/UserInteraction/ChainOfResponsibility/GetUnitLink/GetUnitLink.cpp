//
// Created by Artem Butko on 20/05/2020.
//

#include "GetUnitLink.h"

void GetUnitLink::chain(std::string command, std::string player)
{
    if (command == "/get")
    {
        int number;
        if (player[0] == 'B') number = 0;
        else if (player[0] == 'D') number = 1;
        else number = 2;
        if (field->basesOnField[number]->unitCount == 0)
        {
            std::cout << "You don't have any units in your kindom.. Let's create them! " << std::endl;
            Chain::chain("/create", player);
        }
        else
        {
            while (true)
            {
                try
                {
                    ICommand* Command = new GetUnitCommand(field, player);
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
    }
    else Chain::chain(command, player);
}
