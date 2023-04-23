#include <iostream>

namespace stepik{
  template <typename T>
  class shared_ptr{
    template <typename TT>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T* _ptr = nullptr):
        ptr(_ptr),number(new unsigned int(1)){
      // implement this
    }

    ~shared_ptr(){
        reduce_number();
    }

    template<typename TT>
    shared_ptr(const shared_ptr<TT> & other):
        ptr(other.ptr),number(other.number){
      (*number)++;
    }

    template<typename TT>
    shared_ptr& operator=(const shared_ptr<TT> & other){
        if (*this!= other){
            reduce_number();
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
        reduce_number();
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
    void reduce_number(){
        (*number)--;
        if(*number == 0){
            delete ptr;
            delete number;
        }
    }

    T* ptr;
    unsigned int* number;
    // data members
  };      
} // namespace stepik


class Item
{
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};

int main(){

    using stepik::shared_ptr;
    Item* item = new Item;

    shared_ptr<Item> p1(item);
    shared_ptr<Item> p2;
    p2 = p1;
    std::cout<<p2.use_count()<<"\n";


    return 0;
}