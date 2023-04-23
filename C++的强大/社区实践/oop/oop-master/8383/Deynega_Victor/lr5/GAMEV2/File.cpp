#include "File.h"

File::File(const std::string& fileName) {
    file.open(fileName, std::ios::out | std::ios::app);
}

File::File(const std::string& fileName, bool flag) {
    file.open(fileName, std::ios::in);
}

void  File::write(std::string& message) {
    file << message;
}

std::string File::read(std::string& message) {
   // std::string newA;
    //file >> newA;
    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(message));
    return message;
}

bool File::isOpen() {
    return file.is_open();
}

File::~File() {
    file.close();
}