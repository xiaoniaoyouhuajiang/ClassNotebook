#include <algorithm>


namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0):pointer(ptr), count(new long(1))
    {
    }

    ~shared_ptr()
    {
      count_dec();
    }

      template <class Y>
      friend class shared_ptr;

    template <class Y>
    shared_ptr(const shared_ptr<Y> & other):pointer(other.pointer), count(other.count)
    {
        (*count)++;
        std::cout << "prov";

    }

    template <class Y>
    shared_ptr& operator=(const shared_ptr<Y> & other)
    {
        if (*this != other){
            count_dec();
            pointer = other.pointer;
            count = other.count;
            (*count)++;
        }
        return *this;
    }

    template <class Y>
    bool operator==(const shared_ptr<Y> & other) const
    {
        return pointer == other.pointer;
    }

    template <class Y>
    bool operator!=(const shared_ptr<Y> & other) const
    {
        return pointer != other.pointer;
    }

    explicit operator bool() const
    {
      return pointer != nullptr;
    }

    T* get() const
    {
      return pointer;
    }

    long use_count() const
    {
      return pointer ? *count : 0;
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
        std::swap(pointer, x.pointer);
        std::swap(count,   x.count);
    }

    void reset(T *ptr = 0)
    {
        count_dec();
        this->pointer = ptr;
        count = new long(1);
    }

  private:
    T    * pointer;
    long * count;

    void count_dec(){
        if (--(*count) == 0){
            delete pointer;
            delete count;
        }
    }
  };
} // namespace stepik

