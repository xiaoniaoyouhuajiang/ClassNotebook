
#ifndef IHANDLER_H
#define IHANDLER_H

#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <map>
#include "memento.h"

// define ahead
class TxtWriter;
class TxtReader;
class BinaryReader;
class BinaryWriter;


class IBackupable {
public:
    virtual Memento* makeBackup() const = 0;
    virtual void restore(Memento *m) = 0;
    virtual ~IBackupable();
};
class Unit {
private:
protected:
    Unit(std::size_t noInp, std::size_t noOut) : noInp(noInp), noOut(noOut), isOutput(false){
        this->id = idSerial++;
    }
    static std::size_t idSerial;
public:
    std::size_t id;
    std::size_t noInp;
    std::size_t noOut;
    std::size_t type;
    bool isOutput;
    virtual void setNext(std::size_t slot, Unit* handler) = 0;
    virtual void setNext(std::size_t slot, std::shared_ptr<Unit> handler) = 0;
    virtual std::vector<std::size_t> getNexts() = 0;
    virtual Unit* getNextU(std::size_t slot) = 0;

    virtual bool verify() const = 0;

    virtual std::string toString(){
        return "Unit "+std::to_string(id);
    }
    virtual Unit* clone() = 0;
    virtual ~Unit();
};

template <typename T>
class IHandler{
public:
    virtual void handle (T inp) = 0;
    virtual ~IHandler(){}
};

template <typename T>
class IMultiInputHandler : public IHandler<T>{
public:
    using IHandler<T>::handle;
    virtual void handle(std::size_t noInp, T *inp){
        for(std::size_t i = 0;i<noInp;i++){
            handle(inp[i]);
        }
    }
    virtual ~IMultiInputHandler(){}
};
template <typename U>
class HandlerOutput : public IBackupable{
private:
    std::size_t output_size;
protected:
    std::unique_ptr<U[]> results;
    std::unique_ptr<IHandler<U>*[]> nexts;
    HandlerOutput(std::size_t noOut):output_size(noOut), results(new U[noOut]), nexts(new IHandler<U>*[noOut]){
        for(std::size_t i = 0; i<noOut;i++){
            this->results[i]=U();
            this->nexts[i] = nullptr;
        }
    }
    virtual Memento* makeBackup() const{
        unsigned char *stateData = (unsigned char *)results.get();
        return new Memento(stateData,sizeof(U)*this->output_size);
    }
    virtual void restore(Memento *m){
        U* res = new U[this->output_size];
        std::copy(m->state,m->state+sizeof(U)*this->output_size,(unsigned char *)res);
        results.reset(res);
    }

public:
    std::size_t getSize(){
        return output_size;
    }
    std::size_t getElementSize(){
        return sizeof(U);
    }
    virtual U* getResult() const{
        return results.get();
    }

    virtual IHandler<U>* getNext(std::size_t slot){
        return this->nexts[slot];
    }


    virtual void setNext(std::size_t slot, IHandler<U>* handler) = 0;
    virtual void setNext(std::size_t slot, std::shared_ptr<IHandler<U>> handler) = 0;

    template <typename T>
    friend TxtWriter& operator<<(TxtWriter& os, HandlerOutput<T> *obj);

    template <typename T>
    friend TxtReader& operator>>(TxtReader& os, HandlerOutput<T> *obj);

    template <typename T>
    friend BinaryWriter& operator<<(BinaryWriter& os, HandlerOutput<T> *obj);

    template <typename T>
    friend BinaryReader& operator>>(BinaryReader& os, HandlerOutput<T> *obj);

    virtual ~HandlerOutput(){}
};
#endif // IHANDLER_H
