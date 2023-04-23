
#include "File.h"

File::File(const std::string& fileName, std::string mode) : isFileOpen(true)
{
    if (mode == "save") file.open(fileName, std::ios::out | std::ios::trunc);
    else file.open(fileName, std::ios::in);
}

void File::writeString(std::string str)
{
    file << str << std::endl;
}

File::~File()
{
    file.close();
}

std::stringstream File::readString()
{
    std::string string;
    std::stringstream stream ;
    if (file.eof()) stream << 0;
    else
    {
        stream << 1 << std::endl;
        stream << file.rdbuf();
    }
    return stream;
}