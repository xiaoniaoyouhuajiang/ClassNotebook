#include <string>
#include "BaseInfoLink.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/BaseCommands/BaseInfoReuqest.h"

void BaseInfoLink::chain(std::string command, std::string player)
{
    if (command == "/info")
    {
        IRequest* Command = new BaseInfoReuqest(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);
}