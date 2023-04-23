#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <utility>
#include <iostream>

using namespace std;

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
    typedef T value_type;
    typedef size_t size_type;
      
  public:
    explicit shared_ptr(value_type *ptr = 0)
    {
      _ptr = ptr;
      if(ptr) {
          count = new size_t(1);
      } else {
          count = nullptr;
      }
    }

    ~shared_ptr()
    {
      if(use_count() > 1) {
        --(*count);
      } else {
        delete _ptr;
        delete count;
        _ptr = nullptr;
        count = nullptr;
      }
    }

    shared_ptr(const shared_ptr &other)
    {
      _ptr = other.get();
      count = other.get_count();
      if(use_count()) {
        ++(*count);        
      }
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(this != &other) {
        this->~shared_ptr();
        if(other.get()) {
          _ptr = other.get();
          count = other.get_count();
          if(use_count()) {
            ++(*count);
          }
        } else {
          _ptr = nullptr;
          count = nullptr;
        }
      }
      return *this;
    }
    
    template <class U>
    shared_ptr(const shared_ptr<U> &other)
    {
      _ptr = other.get();
      count = other.get_count();
      if(use_count()) {
        ++(*count);        
      }
      cout << "U_Constr" << endl;
    }
    
    template <class U>
    shared_ptr& operator=(const shared_ptr<U> &other)
    {
      if(get() != other.get()) {
        this->~shared_ptr();
        if(other.get()) {
          _ptr = other.get();
          count = other.get_count();
          if(use_count()) {
            ++(*count);        
          }
        } else {
          _ptr = nullptr;
          count = nullptr;
        }
      }
      cout << "U_Constr =" << endl;
      return *this;
    }
    
    explicit operator bool() const
    {
      return get() != nullptr;
    }

    value_type* get() const
    {
      return _ptr;
    }
    
    size_type* get_count() const {
      return count;
    }
    
    size_t use_count() const
    {
      if (_ptr) {
          return *count;
      } else {
          return 0;
      }
    }

    value_type& operator*() const
    {
      return *_ptr;
    }

    value_type* operator->() const
    {
      return _ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(*this, x);
    }

    void reset(value_type *ptr = 0)
    {
      shared_ptr<value_type>(ptr).swap(*this);    
    }
    
  private:
    value_type *_ptr;
    size_type *count;
  };
  
  template <class U, class V>
  bool operator==(const shared_ptr<U> &rhs, const shared_ptr<V> &lhs)
  {
    return lhs.get() == rhs.get();
  }
} // namespace stepik

#endif // !SHARED_PTR_H
