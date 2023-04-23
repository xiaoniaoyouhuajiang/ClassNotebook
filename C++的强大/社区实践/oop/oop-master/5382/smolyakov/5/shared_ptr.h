#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <utility>
namespace stepik
{

  template <typename T>
  class shared_ptr
  {
    template <typename Y>
    friend class shared_ptr;

  public:

    shared_ptr()
      :element_type(nullptr)
      ,count(nullptr)
    {
    }

    explicit shared_ptr(T *ptr)
      :element_type(ptr)
      ,count(ptr ? new int(1) : nullptr)
    {
    }

    ~shared_ptr() {
      ifDeleteElement();
    }


    template <typename Y>
    shared_ptr<T>(const shared_ptr<Y> & other);

    shared_ptr(const shared_ptr<T>& other);

    template <typename Y>
    shared_ptr<T>& operator=(const shared_ptr<Y>& other);

    shared_ptr& operator=(const shared_ptr& other);

    template <typename Y>
    bool operator==(const shared_ptr<Y> &other) const;


    bool operator==(const shared_ptr<T> &other) const;

    explicit operator bool() const;

    T* get() const;

    long use_count() const;

    T& operator*() const;

    T* operator->() const;

    void swap(shared_ptr& x) noexcept;

    void reset(T *ptr = nullptr);

  private:
    T* element_type;
    int *count;

    void ifDeleteElement();
  };
} // namespace stepik
#endif
