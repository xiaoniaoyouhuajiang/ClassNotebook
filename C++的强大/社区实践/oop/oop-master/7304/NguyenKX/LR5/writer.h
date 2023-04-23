
#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "ihandler.h"
#include "coordinate.h"
class IWriter {
public:
    std::ofstream os;
    virtual void write(std::string message) = 0;
    virtual ~IWriter() {}
};

class TxtWriter : public IWriter{
private:
public:
    TxtWriter(std::string fileName, bool isAppend = false){
        if(isAppend)
            os.open(fileName, std::fstream::out | std::fstream::app);
        else
            os.open(fileName);
    }

    virtual void write(std::string message){
        os << message << std::endl;
    }

    template <typename T>
    friend TxtWriter& operator<<(TxtWriter& os, HandlerOutput<T> *obj)
    {
        for(std::size_t i = 0; i< obj->getSize();i++){
            os.os<< (obj->getResult())[i]<<" ";
        }
        os.os<<std::endl;
        return os;
    }

    friend TxtWriter& operator<<(TxtWriter& os, std::size_t obj)
    {
        os.os<< obj<<std::endl;
        return os;
    }

    virtual ~TxtWriter(){
        os.close();
    }
};

class BinaryWriter : public IWriter{
public:
    BinaryWriter(){
    }

    BinaryWriter(std::string fileName){
        os.open(fileName, std::fstream::out | std::fstream::binary);
    }

    virtual void write(std::string message){
        os << message << std::endl;
    }

    virtual ~BinaryWriter(){
        os.close();
    }

    template <typename T>
    friend BinaryWriter& operator<<(BinaryWriter& os, HandlerOutput<T> *obj){
        os.os.write((char*)obj->getResult(),obj->getSize()*obj->getElementSize());
        return os;
    }

    friend BinaryWriter& operator<<(BinaryWriter& os, std::size_t obj){
        os.os.write((char*)obj,sizeof(obj));
        return os;
    }
};



class BufferedWriter : public IWriter{
private:
    IWriter *writer;
    std::stringstream buffer;
public:
    BufferedWriter(IWriter *writer) : writer(writer), buffer(""){}

    virtual void write(std::string message){
        buffer<<message<<std::endl;
        if(buffer.str().length()>200)
        {
            writer->write(buffer.str());
            buffer.str( std::string() );
            buffer.clear();
        }
    }
    void save(){
        writer->write(buffer.str());
        buffer.str( std::string() );
        buffer.clear();
    }
    virtual ~BufferedWriter(){
        save();
        delete writer;

    }
};


inline TxtWriter& operator<<(TxtWriter& os, Unit *obj)
{
    if(dynamic_cast<HandlerOutput<int>*>(obj)!=nullptr){
        return os<<dynamic_cast<HandlerOutput<int>*>(obj);
    }else if(dynamic_cast<HandlerOutput<double>*>(obj)!=nullptr){
        return os<<dynamic_cast<HandlerOutput<double>*>(obj);
    }else if(dynamic_cast<HandlerOutput<Coordinate>*>(obj)!=nullptr){
        return os<<dynamic_cast<HandlerOutput<Coordinate>*>(obj);
    }
    return os;
}
inline BinaryWriter& operator<<(BinaryWriter& os, Unit *obj)
{
    if(dynamic_cast<HandlerOutput<int>*>(obj)!=nullptr){
        return os<<dynamic_cast<HandlerOutput<int>*>(obj);
    }else if(dynamic_cast<HandlerOutput<double>*>(obj)!=nullptr){
        return os<<dynamic_cast<HandlerOutput<double>*>(obj);
    }else if(dynamic_cast<HandlerOutput<Coordinate>*>(obj)!=nullptr){
        return os<<dynamic_cast<HandlerOutput<Coordinate>*>(obj);
    }
    return os;
}

#endif // WRITER_H
