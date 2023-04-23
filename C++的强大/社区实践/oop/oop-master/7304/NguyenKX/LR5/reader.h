#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include "ihandler.h"
#include "coordinate.h"
class IReader {
public:
    virtual ~IReader() {}
};
class TxtReader : public IReader{
public:
    std::ifstream is;
    TxtReader(std::string fileName){
        is.open(fileName, std::fstream::in);
    }

    template <typename T>
    friend TxtReader& operator>>(TxtReader& is, HandlerOutput<T> *obj){
        for(std::size_t i = 0; i< obj->getSize();i++){
            is.is>>(obj->getResult())[i];
        }
        return is;
    }

    friend TxtReader& operator>>(TxtReader& is, std::size_t &obj){
        is.is>>obj;
        return is;
    }

    virtual ~TxtReader(){
        is.close();
    }
};


class BinaryReader : public IReader{
public:
    std::ifstream is;
    BinaryReader(std::string fileName){
        is.open(fileName, std::fstream::in | std::fstream::binary);
    }

    template <typename T>
    friend BinaryReader& operator>>(BinaryReader& is, HandlerOutput<T> *obj){
        is.is.read((char*)obj->getResult(),obj->getSize()*obj->getElementSize());
        return is;
    }

    friend BinaryReader& operator>>(BinaryReader& is, std::size_t &obj){
        is.is.read((char*)obj,sizeof(obj));
        return is;
    }

    virtual ~BinaryReader(){
        is.close();
    }
};
inline TxtReader& operator>>(TxtReader& is, Unit *obj)
{
    if(dynamic_cast<HandlerOutput<int>*>(obj)!=nullptr){
        return is>>dynamic_cast<HandlerOutput<int>*>(obj);
    }else if(dynamic_cast<HandlerOutput<double>*>(obj)!=nullptr){
        return is>>dynamic_cast<HandlerOutput<double>*>(obj);
    }else if(dynamic_cast<HandlerOutput<Coordinate>*>(obj)!=nullptr){
        return is>>dynamic_cast<HandlerOutput<Coordinate>*>(obj);
    }
    return is;
}
inline BinaryReader& operator>>(BinaryReader& is, Unit *obj)
{
    if(dynamic_cast<HandlerOutput<int>*>(obj)!=nullptr){
        return is>>dynamic_cast<HandlerOutput<int>*>(obj);
    }else if(dynamic_cast<HandlerOutput<double>*>(obj)!=nullptr){
        return is>>dynamic_cast<HandlerOutput<double>*>(obj);
    }else if(dynamic_cast<HandlerOutput<Coordinate>*>(obj)!=nullptr){
        return is>>dynamic_cast<HandlerOutput<Coordinate>*>(obj);
    }
    return is;
}


#endif // READER_H
