#include <algorithm>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  private:
    struct Ptr{
      T* value;
      unsigned int count;
    };
    template <typename D>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0)
    {
      if(ptr != nullptr){
        this->ptr = new Ptr;
        this->ptr->value = ptr;
        this->ptr->count = 1;
      }
      else this->ptr = nullptr;
    }

    ~shared_ptr()
    {
      if(ptr != nullptr) 
        if(ptr->count == 1){
          delete ptr->value;
          delete ptr;
        }
        else ptr->count -= 1;
    }

    shared_ptr(const shared_ptr & other)
    {
      ptr = other.ptr;
      if(ptr != nullptr)
        ptr->count += 1;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(ptr == other.ptr)
        return *this;
      this->~shared_ptr();
      ptr = other.ptr;
      if(ptr != nullptr)
        ptr->count += 1;
      return *this;
    }
      
    template <typename D>
    shared_ptr(const shared_ptr<D> & other)
    {
      T* p = dynamic_cast<T*>(other.ptr->value);
      ptr = reinterpret_cast<shared_ptr::Ptr*>(other.ptr);
      ptr->count += 1;
    }
      
    template <typename D>
    shared_ptr& operator=(const shared_ptr<D> & other)
    {
      T* p = dynamic_cast<T*>(other.get());
      ptr = reinterpret_cast<shared_ptr::Ptr*>(other.ptr);
      ptr->count += 1;
    }
     
    explicit operator bool() const
    {
      return ptr != nullptr;
    }

    T* get() const
    {
      if(ptr != nullptr)
        return ptr->value;
      else return nullptr;
    }

    long use_count() const
    {
      if(ptr == nullptr)
        return 0;
      return ptr->count;
    }

    T& operator*() const
    {
      if(ptr != nullptr)
        return *ptr->value;
    }

    T* operator->() const
    {
      if(ptr != nullptr)
        return ptr->value;
      else return nullptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(ptr, x.ptr);
    }

    void reset(T *ptr = 0)
    {
      this->~shared_ptr();
      if(ptr != nullptr){
        this->ptr = new Ptr;
        this->ptr->value = ptr;
        this->ptr->count = 1;
      }
      else this->ptr = nullptr;    
    }

  private:
    Ptr *ptr;
  };

  template <typename T, typename D>
  bool operator==(shared_ptr<T> & ptr1, shared_ptr<D> & ptr2)
  {
    D* p1 = dynamic_cast<D*>(ptr1.get());
    if(p1 == nullptr){
      T* p2 = dynamic_cast<T*>(ptr2.get());
      return ptr1.get() == p2;
    }
    return p1 == ptr2.get();
  }

  template <typename T, typename D>
  bool operator!=(shared_ptr<T> & ptr1, shared_ptr<D> & ptr2) 
  {
    D* p1 = dynamic_cast<D*>(ptr1.get());
    if(p1 == nullptr){
      T* p2 = dynamic_cast<T*>(ptr2.get());
      return ptr1.get() != p2;
    }
    return p1 != ptr2.get();
  }
	
  template <typename T, typename D>
  bool operator>=(shared_ptr<T> & ptr1, shared_ptr<D> & ptr2)
  {
    D* p1 = dynamic_cast<D*>(ptr1.get());
    if(p1 == nullptr){
      T* p2 = dynamic_cast<T*>(ptr2.get());
      return ptr1.get() >= p2;
    }
    return p1 >= ptr2.get();
  }

  template <typename T, typename D>
  bool operator<=(shared_ptr<T> & ptr1, shared_ptr<D> & ptr2)
  {
    D* p1 = dynamic_cast<D*>(ptr1.get());
    if(p1 == nullptr){
      T* p2 = dynamic_cast<T*>(ptr2.get());
      return ptr1.get() <= p2;
    }
    return p1 <= ptr2.get();
  }

  template <typename T, typename D>
  bool operator>(shared_ptr<T> & ptr1, shared_ptr<D> & ptr2)
  {
    D* p1 = dynamic_cast<D*>(ptr1.get());
    if(p1 == nullptr){
      T* p2 = dynamic_cast<T*>(ptr2.get());
      return ptr1.get() > p2;
    }
    return p1 > ptr2.get();
  }

  template <typename T, typename D>
  bool operator<(shared_ptr<T> & ptr1, shared_ptr<D> & ptr2)
  {
    D* p1 = dynamic_cast<D*>(ptr1.get());
    if(p1 == nullptr){
      T* p2 = dynamic_cast<T*>(ptr2.get());
      return ptr1.get() < p2;
    }
    return p1 < ptr2.get();
  }      
} // namespace stepik
