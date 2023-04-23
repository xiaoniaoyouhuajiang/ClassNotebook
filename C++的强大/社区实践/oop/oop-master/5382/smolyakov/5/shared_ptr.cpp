#include <utility>
#include "shared_ptr.h"
namespace stepik
{
  template <typename T>
  template <typename Y>
  shared_ptr<T>::shared_ptr(const shared_ptr<Y> &other)
    :element_type(other.element_type)
    ,count(other.count)
  {
    if (count)
      (*count)++;
  }

  template <typename T>
  shared_ptr<T>::shared_ptr(const shared_ptr<T>& other)
    :element_type(other.element_type)
    ,count(other.count)
  {
    if (count)
      (*count)++;
  }

  template <typename T>
  template <typename Y>
  shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<Y>& other)
  {
    shared_ptr<T> tmp(other);
    swap(tmp);
  }

  template <typename T>
  shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other)
  {
    shared_ptr<T> tmp(other);
    swap(tmp);
  }

  template <typename T>
  template <typename Y>
  bool shared_ptr<T>::operator==(const shared_ptr<Y> &other) const
  {
    return (element_type == other.element_type);
  }

  template <typename T>
  bool shared_ptr<T>::operator==(const shared_ptr<T> &other) const
  {
    return (element_type == other.element_type);
  }

  template <typename T>
  shared_ptr<T>::operator bool() const
  {
    return (element_type != nullptr);
  }

  template <typename T>
  T* shared_ptr<T>::get() const
  {
    return element_type;
  }

  template <typename T>
  long shared_ptr<T>::use_count() const
  {
    if (count)
      return (*count);
  }

  template <typename T>
  T& shared_ptr<T>::operator*() const
  {
    if (element_type)
      return *element_type;
  }

  template <typename T>
  T* shared_ptr<T>::operator->() const
  {
    return element_type;
  }

  template <typename T>
  void shared_ptr<T>::swap(shared_ptr& x) noexcept
  {
    std::swap(element_type,x.element_type);
    std::swap(count,x.count);
  }

  template <typename T>
  void shared_ptr<T>::reset(T *ptr)
  {
    ifDeleteElement();
    element_type = ptr;
    count = !ptr ? nullptr : new int(1);
  }

  template <typename T>
  void shared_ptr<T>::ifDeleteElement() {
    if (count) {
      if (*count <= 1) {
        delete count;
        delete element_type;
        count = nullptr;
        element_type = nullptr;
      }
      else
        (*count)--;
    }
  }
} // namespace stepik
