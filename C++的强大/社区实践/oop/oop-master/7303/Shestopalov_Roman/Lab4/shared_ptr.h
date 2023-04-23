#ifndef SHARED_PTR_H
#define SHARED_PTR_H
  template <typename T>
  class shared_ptr{
    template <typename TT>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T* _ptr = nullptr):
        ptr(_ptr),number(new unsigned int(1)){
    }

    ~shared_ptr(){
        reduce_count();
    }

    template<typename TT>
    shared_ptr(const shared_ptr<TT> & other):
        ptr(other.ptr),number(other.number){
      (*number)++;
    }

    template<typename TT>
    shared_ptr& operator=(const shared_ptr<TT> & other){
        if (*this!= other){
            reduce_count();
            ptr = other.ptr;
            number = other.number;
            (*number)++;
        }
        return *this;
    }

    explicit operator bool() const{
        return ptr != nullptr;
    }

    T* get() const{
        return ptr;
    }

    long use_count() const{
        return (ptr == nullptr)? 0 :*number;
    }

    T& operator*() const{
        return *ptr;
    }

    T* operator->() const{
        return ptr;
    }

    void swap(shared_ptr& x) noexcept{
        std::swap(ptr,x.ptr);
        std::swap(number,x.number);
    }

    void reset(T* _ptr = nullptr){
        reduce_count();
        ptr = _ptr;
        number = new unsigned int(1);
    }

    template<typename TT>
    bool operator == (const shared_ptr<TT>& other)const{
        return ptr == other.ptr;
    }

    template<typename TT>
    bool operator != (const shared_ptr<TT>& other)const{
        return ptr != other.ptr;
    }

  private:
    void reduce_count(){
        (*number)--;
        if(*number == 0){
            delete ptr;
            delete number;
        }
    }

    T* ptr;
    unsigned int* number;
  };
#endif // SHARED_PTR_H
