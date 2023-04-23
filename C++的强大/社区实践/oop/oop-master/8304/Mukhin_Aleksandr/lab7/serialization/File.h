#ifndef LAB2_FILE_H
#define LAB2_FILE_H


#include "Save.h"
#include <memory>
#include <fstream>

class File {
private:
    std::shared_ptr<Save> save = nullptr;

public:
    explicit File(std::shared_ptr<Save> save) : save(save) {}
    std::shared_ptr<Save> get_save();
};


#endif
