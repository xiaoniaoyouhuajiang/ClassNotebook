#pragma once

#include <QString>

class Exception{
private:
    unsigned int lineOfError;
    QString title;
    QString description;
public:
    Exception(unsigned int line,
              QString title,
              QString description){
        this->lineOfError = line;
        this->title = title;
        this->description = description;
    }

    unsigned int getLine() {return lineOfError;}
    QString getTitle() { return title; }
    QString getDescription() { return description; }
};
