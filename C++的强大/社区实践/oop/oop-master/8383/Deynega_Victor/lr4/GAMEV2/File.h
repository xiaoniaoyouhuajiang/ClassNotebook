#include <iostream>
#include <fstream>

class File {
public:
    std::ofstream out;
    File(const std::string& fileName);
    ~File();
    void write(std::string& message);      
};