
#include <string>
#include "CreateBaseLink.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/BaseCommands/CreateBaseRequest.h"


void CreateBaseLink::chain(std::string command, std::string player)
{
    if (command == "/create_base")
    {
        IRequest* Command = new CreateBaseRequest(field);
        Command->Command();
    }
    else Chain::chain(command, player);
}