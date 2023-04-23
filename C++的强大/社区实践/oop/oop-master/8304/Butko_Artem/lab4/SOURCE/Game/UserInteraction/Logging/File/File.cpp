//
// Created by Artem Butko on 21.05.2020.
//

#include "File.h"

File::File(const char* fileName) : isFileOpen(true)
{
    this->file = std::fopen(fileName, "w+");
    if (!this->file) return;
}

bool File::isOpen()
{
    return isFileOpen;
}

File::~File()
{
    std::fclose(this->file);
}

void File::writeString(const char *string)
{
    if (std::fputs(string, file) == EOF) return;
}

