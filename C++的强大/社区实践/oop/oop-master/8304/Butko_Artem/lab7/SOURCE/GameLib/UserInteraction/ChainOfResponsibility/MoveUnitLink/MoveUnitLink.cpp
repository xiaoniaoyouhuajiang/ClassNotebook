//
// Created by Artem Butko on 20/05/2020.
//

#include "MoveUnitLink.h"


void MoveUnitLink::chain(std::string command, std::string player)
{
    if (command == "/move")
    {
        while (true)
        {
            try
            {
                ICommand* Command = new MoveUnitCommand(field, player);
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
