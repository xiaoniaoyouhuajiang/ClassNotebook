#include "../headers/parser.hpp"
#include "../headers/exceptions.hpp"

ParsedStruct CommandParser::parse(std::string command) {
    if (command.length() > 3)
        throw UnknownCommandException();
    ParsedStruct strc = {command[0], command[2]};
    return strc;
}