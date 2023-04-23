#pragma once

#include <cstddef>
#include <iostream>
using namespace std;

namespace stepik {
  template <typename T>
  class shared_ptr {

  template <typename K>
  friend class shared_ptr;
  
  public:
   explicit shared_ptr(T *ptr = 0) :ptr(ptr), count(ptr ? new size_t(1) : nullptr) {}

    ~shared_ptr() {
        if (ptr && count) { 
            if (*count == 1) { 
                delete count; 
                delete ptr;
            } 
            else (*count)--; 
        } 
    }

    shared_ptr(const shared_ptr & other) {
        if (other.get()) { 
            ptr = other.get(); 
            count = other.count; 
            ++*count; 
        } 
        else { 
            ptr = nullptr; 
            count = nullptr; 
        } 
    }

    template <typename K>
    shared_ptr(const shared_ptr<K> & other) {
    cout << "The copy constructor is invoked" << endl;
        if (other.get()) { 
            ptr = other.get(); 
            count = other.count; 
            ++*count; 
        } 
        else { 
            ptr = nullptr; 
            count = nullptr; 
        } 
    }

    shared_ptr& operator=(const shared_ptr & other) {
        shared_ptr m_ptr (other);
        swap(m_ptr);
    }

    template <typename K>
    shared_ptr& operator=(const shared_ptr<K> & other) {
        cout << "The assigment operator is invoked" << endl;
        shared_ptr m_ptr (other);
        swap(m_ptr);
    }

    explicit operator bool() const {
       return (ptr!=nullptr);
    }

    T* get() const {
        return ptr;
    }

    long use_count() const {
        if (count) 
            return *count;
        else return 0;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
      return ptr;
    }

    template <typename K>
    bool operator == (const shared_ptr<K> &other) const {
        return (ptr == other.get());
    }

    template <typename K>
    bool operator != (const shared_ptr<K> &other) const{
        return (ptr != other.get());
    }

    void swap(shared_ptr& x) noexcept {
        std::swap (ptr, x.ptr);
        std::swap (count, x.count);
    }

    void reset(T *ptr = 0) { //Заменяет указатель, который удерживает переменная
        shared_ptr m_ptr (ptr);
        shared_ptr(m_ptr).swap(*this);   
    }

  private:
  T *ptr; 
  size_t *count; 
  };      
} // namespace stepik
