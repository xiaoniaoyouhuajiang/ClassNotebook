//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_FILELOGGER_H
#define OOPROJECT_FILELOGGER_H

#include <string>
#include <cassert>
#include <fstream>
class FileLogger {
private:
    std::string fileName;

    std::ofstream ostream1;
public:
    FileLogger(const std::string &fileName) : fileName(fileName) {
        ostream1.open(fileName,std::ios_base::out);
        if(!ostream1.is_open()){
            assert(0);//Cant open file
        }
    }

    void logToFile(std::string str){
        ostream1<<"F_LOG: "<<str<<std::endl;
    }

    virtual ~FileLogger() {
        ostream1.close();
    }
};


#endif //OOPROJECT_FILELOGGER_H
