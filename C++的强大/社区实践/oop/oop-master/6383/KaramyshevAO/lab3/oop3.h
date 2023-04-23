namespace stepik
{
  template <typename T>
  class shared_ptr{
    template <typename T1>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr_ = 0) : ptr(ptr_), count(new long(1)){}

    ~shared_ptr(){
        del();
    }

    shared_ptr(const shared_ptr & other) : ptr(other.ptr), count(other.count){
        if(count) ++(*count);
    }

    template <typename T1>
    shared_ptr(const shared_ptr<T1> & other) : ptr(other.ptr), count(other.count){
        if(count) ++(*count);
    }

    shared_ptr& operator=(const shared_ptr & other){
        if(ptr!= other.ptr){
            del();
            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }

    template <typename T1>
    shared_ptr& operator=(const shared_ptr<T1> & other){
        if(ptr!= other.ptr){
            del();
            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }

    explicit operator bool() const{
      return ptr!=nullptr;
    }

    T* get() const{
      return ptr;
    }

    long use_count() const{
      return (ptr) ? (*count) : 0;
    }

    T& operator*() const{
      return *(ptr);
    }

    T* operator->() const{
      return ptr;
    }

    void swap(shared_ptr& x) noexcept{
        shared_ptr tmp(x);
        x=*this;
        *this=tmp;
    }

    void reset(T *ptr = 0){
        shared_ptr tmp(ptr);
        swap(tmp);
    }

    template <typename T1>
    bool operator== (const shared_ptr<T1>& other) const {
        return ptr == other.ptr;
    }
    template <typename T1>
    bool operator!= (const shared_ptr<T1>& other) const {
        return ptr != other.ptr;
    }
    template <typename T1>
    bool operator< (const shared_ptr<T1>& other) const {
        return ptr < other.ptr;
    }
    template <typename T1>
    bool operator> (const shared_ptr<T1>& other) const {
        return ptr > other.ptr;
    }
    template <typename T1>
    bool operator<= (const shared_ptr<T1>& other) const {
        return ptr <= other.ptr;
    }
    template <typename T1>
    bool operator>= (const shared_ptr<T1>& other) const {
        return ptr >= other.ptr;
    }

  protected:
    void del(){
        if(--(*count)==0){
            delete count;
            delete ptr;
        }
    }

    T* ptr;
    long *count;
  };
}
