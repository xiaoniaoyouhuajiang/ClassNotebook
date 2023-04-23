#include "MoveUnitLink.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/UnitCommands/MoveUnitRequest.h"

void MoveUnitLink::chain(std::string command, std::string player)
{
    if (command == "/move")
    {
        while (true)
        {
            try
            {
                IRequest* Command = new MoveUnitRequest(field, player);
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