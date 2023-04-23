
#include "SkipLink.h"
#include "../Commands/IRequest.h"
#include "../Commands/DefaultCommand/SkipRequest.h"

void SkipLink::chain(std::string command, std::string player)
{
    if (command == "/skip")
    {
        IRequest* Command = new SkipRequest(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);
}