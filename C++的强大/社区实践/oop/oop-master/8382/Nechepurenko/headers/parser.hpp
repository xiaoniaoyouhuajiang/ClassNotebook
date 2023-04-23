#pragma once
#include <string>

struct ParsedStruct {
    char command;
    char arg;
};

class CommandParser {
public:
    ParsedStruct parse(std::string command);
};