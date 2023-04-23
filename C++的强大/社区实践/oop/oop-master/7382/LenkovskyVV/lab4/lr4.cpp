#include <algorithm>
#include <iostream>
using namespace std;

namespace stepik
{
template <typename T>
  class shared_ptr
  {
      template <typename object>
      friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0):pointer(ptr),count(new unsigned(1)){}

    ~shared_ptr()
    {
        if(use_count()>0)
            minusCount();
        else{
            delete count;
            delete pointer;
            pointer=nullptr;
            count=nullptr;
        }
    }

    shared_ptr(const shared_ptr & other){
        addPointer(other);
    }

    template <typename object>
    shared_ptr(const shared_ptr<object>& other){
        addPointer(other);
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(pointer!=other.pointer){
          this->~shared_ptr();
          addPointer(other);
      }
      return *this;
    }

    template <typename object>
    shared_ptr& operator=(const shared_ptr<object>& other){
        if(pointer!=other.pointer){
	    this->~shared_ptr();
            addPointer(other);
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
        return pointer== NULL?0:(*count);
    }

    T& operator*() const
    {
        return (*pointer);
    }

    T* operator->() const
    {
        return pointer;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(pointer,x.pointer);
        std::swap(count,x.count);
    }

    void reset(T *ptr = 0)
    {
	this->~shared_ptr();
        pointer=ptr;
        count=new unsigned(1);
    }

  private:
    T* pointer;
    unsigned *count;

    void plusCount(){(*count)++;}

    void minusCount(){(*count)--;}

    void addPointer(const shared_ptr & other){
        pointer=other.pointer;
        count=other.count;
        plusCount();
    }

    template <typename object>
    void addPointer(const shared_ptr<object> & other){
        this->pointer=other.pointer;
        this->count=other.count;
        plusCount();
    }
  };
}; // namespace stepik

int main(){
int first=10;
int second=40;
int *res = new int(30);
stepik::shared_ptr<int> ptr1(&first);
stepik::shared_ptr<int> ptr2(&second);
cout<<"First:  "<<*ptr1<<" "<<"First count:  "<<ptr1.use_count()<<endl;
cout<<"Second: "<<*ptr2<<" "<<"Second count: "<<ptr2.use_count()<<endl;
if(ptr1 == ptr2)
	cout<<"First = Second"<<endl;
else
	cout<<"First != Second"<<endl;
cout<<"Swap:"<<endl;
ptr1.swap(ptr2);
cout<<"First:  "<<*ptr1<<" "<<"First count:  "<<ptr1.use_count()<<endl;
cout<<"Second: "<<*ptr2<<" "<<"Second count: "<<ptr2.use_count()<<endl;
cout<<"Reset:"<<endl;
ptr1.reset(res);
cout<<"First:  "<<*ptr1<<" "<<"First count:  "<<ptr1.use_count()<<endl;
cout<<"Second: "<<*ptr2<<" "<<"Second count: "<<ptr2.use_count()<<endl;
return 0;
}
