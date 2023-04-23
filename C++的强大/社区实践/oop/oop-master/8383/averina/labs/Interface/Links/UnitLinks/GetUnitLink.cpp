
#include <string>
#include "GetUnitLink.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/UnitCommands/GetUnitRequest.h"



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
            std::cout << "You don't have this unit in your kindom... Let's create it! " << std::endl;
            Chain::chain("/create", player);
        }
        else
        {
            while (true)
            {
                try
                {
                    IRequest* Command = new GetUnitRequest(field, player);
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