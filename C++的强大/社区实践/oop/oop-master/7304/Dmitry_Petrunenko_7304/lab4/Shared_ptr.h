namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template <typename object>
            friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0):pointer(ptr),counter(new unsigned(1)){}

    ~shared_ptr()
    {
          destroyer();
    }

      template <typename object>
          shared_ptr(const shared_ptr<object>& other){
              this->pointer=other.pointer;
              this->count=other.count;
              (*counter)++;
          }

    shared_ptr(const shared_ptr & other) : pointer(other.pointer), counter(other.counter)
    {
        (*counter)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if(pointer!=other.pointer){
                  destroyer();
                  pointer = other.pointer;
                  counter = other.counter;
                  (*counter)++;
              }
              return *this;
    }
    template <typename object>
        shared_ptr& operator=(const shared_ptr<object>& other){
            if(pointer!=other.pointer){
                destroyer();
                this->pointer=other.pointer;
                this->count=other.count;
                (*counter)++;
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
        return (pointer == NULL) ? 0 : (*counter);
    }

    T& operator*() const
    {
        return *pointer;
    }

    T* operator->() const
    {
        return pointer;
    }

    void swap(shared_ptr& x) noexcept
            {
                std::swap( this->pointer, x.pointer);
                std::swap( this->counter, x.counter);
            }

    void reset(T *ptr = 0)
    {
        shared_ptr x(ptr);
        swap( x );
    }

  private:
    void destroyer(){
            if((*counter)>0)
                 (*counter)--;
                    if((*counter)==0){
                        delete counter;
                        delete pointer;
                    }
        }
    T* pointer;
    unsigned *counter;
  };
} // namespace stepik