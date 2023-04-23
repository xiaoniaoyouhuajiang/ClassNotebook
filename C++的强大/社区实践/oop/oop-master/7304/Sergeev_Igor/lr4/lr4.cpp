#include <algorithm>
#include <iostream>
using namespace std;
namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template <typename next_obj>
      friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0)
    {
      this->my_ptr = ptr;
      this->count = new unsigned;
      *count = 1;
    }

    ~shared_ptr()
    {
      remove_shared();
    }

    shared_ptr(const shared_ptr & other)
    {
      my_ptr = other.my_ptr;
      count = other.count;
      ++(*count);
    }

    template <typename next_obj>
    shared_ptr(const shared_ptr<next_obj> & other)
    {
      this->my_ptr = other.my_ptr;
      this->count = other.count;
      ++(*count);
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if (this != &other){
          remove_shared();
          my_ptr = other.my_ptr;
          count = other.count;
          ++(*count);
      }
      return *this;
    }

    template <typename next_obj>
    shared_ptr& operator=(const shared_ptr<next_obj> & other)
    {
      if (my_ptr != other.my_ptr){
          remove_shared();
          my_ptr = other.my_ptr;
          count = other.count;
          ++(*count);
      }
      return *this;
    }

    template <typename next_obj>
    bool operator==(const shared_ptr<next_obj> & other) const
    {
      return my_ptr == other.my_ptr;
    }


    explicit operator bool() const
    {
      return my_ptr != nullptr;
    }

    T* get() const
    {
      return my_ptr;
    }

    long use_count() const
    {
      return my_ptr == nullptr ? 0 : (*count);
    }

    T& operator*() const
    {
      return *my_ptr;
    }

    T* operator->() const
    {
      return my_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(my_ptr,x.my_ptr);
      std::swap(count,x.count);
    }

    void reset(T *ptr = 0)
    {
      remove_shared();
      my_ptr = ptr;
      count = new unsigned(1);
    }

  private:
     void remove_shared(){
        if ((*count) > 0)
            --(*count);
        if ((*count) == 0){
            delete my_ptr;
            delete count;
        }
      }
      T* my_ptr;
      unsigned* count;
    // data members
  };
} // namespace stepik

class test{
    int val;
};
class number : public test{
    int value;
};

int main(){
    stepik::shared_ptr<number> ptr1(new number());
    stepik::shared_ptr<test> ptr2(ptr1);
    cout << ptr1.use_count() << endl;
    if (ptr1 == ptr2)
        cout << "SAME" << endl;
}
