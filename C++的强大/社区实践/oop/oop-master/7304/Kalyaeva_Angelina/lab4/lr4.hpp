namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template <typename T1> friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0):ptr(ptr), count(new long(1))
    {
    }

    ~shared_ptr()
    {
      delete_ptr();
    }

    shared_ptr(const shared_ptr & other):ptr(other.ptr), count(other.count)
    {
      if(count){
          (*count)++;
      }
    }
      template <typename T1>
      shared_ptr(const shared_ptr<T1> & other):ptr(other.ptr), count(other.count)
    {
      if(count){
          (*count)++;
      }
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(ptr!=other.ptr){
          delete_ptr();
          ptr=other.ptr;
          count=other.count;
          (*count)++;
      }
      return *this;
    }
      
      template <typename T1>
      shared_ptr& operator=(const shared_ptr<T1> & other)
    {
      if(ptr!=other.ptr){
          delete_ptr();
          ptr=other.ptr;
          count=other.count;
          (*count)++;
      }
      return *this;
    }
      template <typename T1>
      bool operator == (const shared_ptr<T1>& other) const{
          return ptr==other.ptr;
      }

    explicit operator bool() const
    {
      return ptr!=nullptr;
    }

    T* get() const
    {
      return ptr;
    }

    long use_count() const
    {
      return (ptr)?(*count):0;
    }

    T& operator*() const
    {
      return *ptr;
    }

    T* operator->() const
    {
      return ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      shared_ptr tmp(x);
      x=*this;
      *this=tmp;
    }

    void reset(T *ptr = 0)
    {
      shared_ptr tmp(ptr);
      swap(tmp);
    }

  private:
    T *ptr;
    long *count;
    void delete_ptr(){
        if((*count)>0){
            (*count)--;
        }
        if((*count)==0){
            delete ptr;
            delete count;
        }
    }
  };      
} // namespace stepik