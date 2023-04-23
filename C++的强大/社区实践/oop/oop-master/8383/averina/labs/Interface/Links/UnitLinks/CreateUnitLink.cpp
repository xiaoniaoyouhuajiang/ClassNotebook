
#include "CreateUnitLink.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/UnitCommands/CreateUnitRequest.h"


void CreateUnitLink::chain(std::string command, std::string player)
{
    if (command == "/create")
    {
        int number;
        if (player[0] == 'B') number = 0;
        else if (player[0] == 'D') number = 1;
        else number = 2;
        if (field->basesOnField[number]->gold == 0)
        {
            std::cout << "You don't have money! Skip & gold!" << std::endl;
            Chain::chain("/skip", player);
        }
        else if (field->basesOnField[number]->unitCount >= field->basesOnField[number]->unitLimit)
        {
            std::cout << "Unit limit reached! Skip & gold!" << std::endl;
            Chain::chain("/skip", player);
        }
        else
        {
            while (true)
            {
                try
                {
                    IRequest* Command = new CreateUnitRequest(field, player);
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