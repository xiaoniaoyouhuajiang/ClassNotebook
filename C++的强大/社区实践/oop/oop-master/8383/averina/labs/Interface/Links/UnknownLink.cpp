
#include "UnknownLink.h"
#include "../Commands/IRequest.h"
#include "../Commands/DefaultCommand/UnknownRequest.h"


void UnknownLink::chain(std::string command, std::string player)
{
    IRequest* Command = new UnknownRequest();
    Command->Command();
}