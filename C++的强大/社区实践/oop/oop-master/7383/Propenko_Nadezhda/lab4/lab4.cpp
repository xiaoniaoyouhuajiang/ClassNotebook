#include <iostream>
namespace stepik
{
  template <typename T>
  class shared_ptr{
    template <typename T2>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0):ptr(ptr), count(ptr ? new long(1) : nullptr){}//конструктор, explicit защищает от непредвиденных неявных преобразований

    ~shared_ptr(){ //деструктор
        Delet();
    }

    shared_ptr(const shared_ptr & other):ptr(other.ptr), count(other.count){//конструктор копирования
      if(ptr) (*count)++;
    }

    shared_ptr& operator=(const shared_ptr & other){
       if (ptr != other.ptr) {//заменяет управляемый объект
           Delet();
           ptr = other.ptr;
           count = other.count;
           if(ptr) (*count)++;
       }
       return *this;
    }
    template <typename T2>
    shared_ptr(const shared_ptr<T2> & other):ptr(other.ptr), count(other.count){//тип T2 должен быть полностью определён и неявно преобразовываться в T
      if(ptr) (*count)++;
    }
    template <typename T2>
    shared_ptr& operator=(const shared_ptr<T2> & other){//тип T2 должен быть полностью определён и неявно преобразовываться в T
       if (ptr != other.ptr) {//заменяет управляемый объект
           Delet();
           ptr = other.ptr;
           count = other.count;
           if(ptr) (*count)++;
       }
       return *this;
    }
    template <typename T2>
    bool operator == (const shared_ptr<T2> & other) const {
        return ptr == other.ptr;
    }

    template <typename T2>
    bool operator != (const shared_ptr<T2> & other) const {
        return ptr != other.ptr;
    }
    explicit operator bool() const{//проверяет, указывает ли указатель на объект
      return ptr != nullptr;
    }

    T* get() const{//возвращает указатель на управляемый объект
      return ptr;
    }

    long use_count() const{//возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
      return (count ? *count : 0);
    }

    T& operator*() const{
      if(ptr) return *ptr;  //ссылка на управляемый объект (куча)
    }

    T* operator->() const{
      return ptr;//указатель на управляемый объект (стек)
    }

    void swap(shared_ptr& x) noexcept{//спецификатор времени компиляции noexcept, которой говорит компилятору о том, что функция не будет выбрасывать исключения
      shared_ptr tmp(x);
      x=*this;
      *this=tmp;
    }

    void reset(T *ptr = 0){ //заменяет объект, которым владеет
      shared_ptr tmp(ptr);
      swap(tmp);
    }

  private:
    T *ptr;//указатель на объект
    long *count;//счетчик ссылок
    void Delet(){
        if(ptr){
            if (*count == 1) {
                delete count;
                delete ptr;
            }
            else (*count)--;
        }
    }
  };
} // namespace stepik
