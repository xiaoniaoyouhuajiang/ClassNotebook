#include <string>
#include "LoggingLink.h"
#include "../Chain.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/LogCommand/LoggingRequest.h"


void LoggingLink::chain(std::string command, std::string player)
{
    if (command == "/logging")
    {
        IRequest* Command = new LoggingRequest(field);
        Command->Command();
    }
    else Chain::chain(command, player);
}