#include "File.h"

File::File(const std::string& fileName) {
    out.open(fileName, std::ios::out | std::ios::app);
}

void  File::write(std::string& message) {
    out << message;
}

File::~File() {
    out.close();
}