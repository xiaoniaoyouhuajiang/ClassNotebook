//
// Created by 1 on 16.03.2019.
//

#ifndef SHARED_SHARED_H
#define SHARED_SHARED_H

#include <algorithm>
#include <iostream>
using namespace std;
template <typename T>
  class shared_ptr
  {
      template <typename object>
      friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0):pointer(ptr),count(new unsigned(1)){}

    ~shared_ptr()
    {
        deleteSharedPtr();
    }

    shared_ptr(const shared_ptr & other){
        addPointer(other);
    }

    template <typename object>
    shared_ptr(const shared_ptr<object>& other){
        addPointer(other);
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(pointer!=other.pointer){
          deleteSharedPtr();
          addPointer(other);
      }
      return *this;
    }

    template <typename object>
    shared_ptr& operator=(const shared_ptr<object>& other){
        if(pointer!=other.pointer){
            deleteSharedPtr();
            addPointer(other);
        }
        return *this;
    }
    template <typename object>
    bool operator==(const shared_ptr<object>& other) const{
        return pointer == other.pointer;
    }

    explicit operator bool() const
    {
        return pointer!= nullptr;
    }

    T* get() const
    {
        return pointer;
    }

    long use_count() const
    {
        return pointer== NULL?0:(*count);
    }

    T& operator*() const
    {
        return (*pointer);
    }

    T* operator->() const
    {
        return pointer;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(pointer,x.pointer);
        std::swap(count,x.count);
    }

    void reset(T *ptr = 0)
    {
        deleteSharedPtr();
        pointer=ptr;
        count=new unsigned(1);
    }

  private:
    T* pointer;
    unsigned *count;
    void plusCount(){(*count)++;}
    void minusCount(){(*count)--;}
    void deleteSharedPtr(){
        if((*count)>0)
            minusCount();
        if((*count)==0){
            delete count;
            delete pointer;
        }
    }
    void addPointer(const shared_ptr & other){
        pointer=other.pointer;
        count=other.count;
        plusCount();
    }
    template <typename object>
    void addPointer(const shared_ptr<object> & other){
        this->pointer=other.pointer;
        this->count=other.count;
        plusCount();
    }
  };
#endif //SHARED_SHARED_H
