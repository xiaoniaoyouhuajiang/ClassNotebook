namespace stepik{
  template <typename T>
  class shared_ptr{
  public:
    template <typename D>
    friend class shared_ptr;

    explicit shared_ptr(T *ptr = 0) : pointer(ptr), count(ptr ? new long(1) : nullptr)
    {}

    ~shared_ptr(){
      if (pointer)
        deleter();
    }

    shared_ptr(const shared_ptr & other){
      pointer = other.pointer;
      count = other.count;
      if (pointer)
        (*count)++;
    }

    template <typename D>
    shared_ptr(const shared_ptr<D> & other){
      pointer = other.pointer;
      count = other.count;
      if (pointer)
        (*count)++;
    }

    shared_ptr& operator=(const shared_ptr & other){
      if (pointer == other.pointer)
        return *this;
      if (pointer)
        deleter();
      pointer = other.pointer;
      count = other.count;
      if (pointer)
        (*count)++;
      return *this;
    }

    template <typename D>
    shared_ptr& operator = (const shared_ptr<D> & other){
      if (pointer != other.pointer){
        if (pointer)
          deleter();
        pointer = other.pointer;
        count = other.count;
        if (pointer)
          (*count)++;
      }
      return *this;
    }

    template <typename D>
    bool operator == (const shared_ptr<D> & other) const{
      return pointer == other.pointer;
    }

    template <typename D>
    bool operator != (const shared_ptr<D> & other) const{
      return pointer != other.pointer;
    }

    explicit operator bool() const{
      if (get())
        return true;
      return false;
    }

    T* get() const{
      return pointer;
    }

    long use_count() const{
      return (count ? *count : 0);
    }

    T& operator*() const{
      return *pointer;
    }

    T* operator->() const{
      return pointer;
    }

    void swap(shared_ptr& x) noexcept{
      std::swap(pointer, x.pointer);
      std::swap(count, x.count);
    }

    void reset(T *ptr = 0){
      if (pointer)
        deleter();
      pointer = ptr;
      if (pointer)
        count = new long(1);
      else count = nullptr;
    }

  private:
    T *pointer;
    long *count;

    void deleter() {
      if ((*count) == 1) {
        delete pointer;
        delete count;
      }
      else (*count)--;
    }
  };
} // namespace stepik
