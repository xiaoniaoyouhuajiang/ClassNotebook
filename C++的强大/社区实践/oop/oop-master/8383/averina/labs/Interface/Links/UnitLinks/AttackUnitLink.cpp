
#include <string>
#include "AttackUnitLink.h"
#include "../../../Exceptions/TypeError.h"
#include "../../../Exceptions/OutofRangeError.h"
#include "../../../Exceptions/LogicalError.h"
#include "../../Commands/UnitCommands/AttackUnitRequest.h"

void AttackUnitLink::chain(std::string command, std::string player)
{
    if (command == "/attack_unit")
    {
        while (true)
        {
            try
            {
                IRequest* Command = new AttackUnitRequest(field, player);
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