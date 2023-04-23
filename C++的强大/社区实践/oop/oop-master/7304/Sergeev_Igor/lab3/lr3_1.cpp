#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using namespace std;
namespace stepik
{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0) : n(count), arr(n ? new value_type[n]() : nullptr)
    {
        m_first = arr;
        m_last = arr + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : n(last-first), arr(n ? new value_type[n]() : nullptr) 
    {
      if (arr != nullptr){
          for (InputIterator it = first;it!=last;++it){
              arr[it-first] = *it;
          }
      }
      m_first = arr;
      m_last = n + arr;
    }
         
    vector(std::initializer_list<Type> init) : n(init.size()), arr(n ? new value_type[n]() : nullptr)
    {
      if (arr != nullptr){
          int ind = 0;
          for (auto &elem : init){
              arr[ind] = elem;
              ind++;
          }
      }
      m_first = arr;
      m_last = n + arr;
    }

    vector(const vector& other)
    {
      vector tmp(other.n);
      for (size_t i = 0; i < tmp.n;i++){
          tmp.arr[i] = other.arr[i];
      }
      n = tmp.n;
      arr = n ? new value_type[n]() : nullptr;
      for (size_t i = 0;i < n;i++){
          arr[i] = tmp.arr[i];
      }
      m_first = arr;
      m_last = n + arr;
    }

    vector(vector&& other)
    {
      arr = other.arr;
      n = other.n;
      other.arr = nullptr;
      other.m_first = nullptr;
      other.m_last = nullptr;
      m_first = arr;
      m_last = n + arr;
    }

    ~vector()
    {
        if (arr)
            delete[] arr;
    }

    vector& operator=(const vector& other)
    {
     if (this != &other)
         vector(other).swap(*this);
     m_first = arr;
     m_last = n + arr;
     return *this;
    }

    vector& operator=(vector&& other)
    {
      // Проверка на самоприсваивание
    if (&other == this)
      return *this;
      // Удаляем всё, что может хранить указатель до этого момента
    delete[] arr;
      m_first = nullptr;
      m_last = nullptr;
      n = other.n;
    arr = other.arr;
      m_first = arr;
      m_last = n + arr;
      other.m_first = nullptr;
      other.m_last = nullptr;
    other.arr = nullptr; 
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      delete[] arr;
      m_first = nullptr;
      m_last = nullptr;
      n = last-first;
      arr = n ? new value_type[n]() : nullptr;
      if (arr != nullptr){
          for (InputIterator it = first;it!=last;++it){
                 arr[it-first] = *it;
          }  
      }
      m_first = arr;
      m_last = arr + n;
    }

     void resize(size_t count)
    {
      vector tmp(n);
      for (size_t i = 0; i < tmp.n;i++){
          tmp.arr[i] = arr[i];
      }
      delete [] arr;
      arr = count ? new value_type[count]() : nullptr;
      if (count <= n){
          for (size_t i=0;i<count;i++)
              arr[i] = tmp.arr[i];
      }
      else if (count > n){
          for (size_t i=0;i<n;i++)
              arr[i] = tmp.arr[i];
      }
      n = count;
      m_first = arr;
      m_last = arr + n;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      int dif = pos - m_first;
      n--;
      vector tmp(n);
      int i=0;
      for (const_iterator it=begin();it!=end();++it){
          if (it == pos)
              continue;
          tmp.arr[i] = *it;
          i++;
      }
      delete [] arr;
      arr = n ? new value_type[n]() : nullptr;
      for (size_t i = 0; i < n;i++){
          arr[i] = tmp.arr[i];
      }
      m_first = arr;
      m_last = arr + n;
      return arr + dif;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      int dif = first-m_first; 
      vector tmp(n);
      size_t j = 0;
      for (const_iterator it = begin();it!=end();++it){
          if (it >= first && it < last){
              continue;
          }
          tmp.arr[j] = *it;
          j++;
      }
      delete [] arr;
      n -= (last-first);
      arr = n ? new value_type[n]() : nullptr;
      for (size_t i = 0; i < n;i++){
          arr[i] = tmp.arr[i];
      }
      m_first = arr;
      m_last = arr + n;
      return arr + dif;
    }

    iterator insert(const_iterator pos, const Type& value)
    {
      int dif = pos - m_first,i = 0;
      n++;
      vector tmp(n);
      for (const_iterator it=begin();it!=end();++it){
          if (it == pos){
              tmp.arr[i] = value;
              i++;
          }
          tmp.arr[i] = *it;
          i++;
      }
      if (pos == end()){
          tmp.arr[i] = value;
      }
      delete [] arr;
      arr = n ? new value_type[n]() : nullptr; 
      for (int j=0;j<n;j++){
          arr[j] = tmp.arr[j];
      }
      m_first = arr;
      m_last = arr + n;
      return arr + dif;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      int dif = pos - m_first,count = 0,i = 0;
      count = last-first;
      vector tmp(n+count);
      for (const_iterator it=begin();it!=end();++it){
          if (it == pos){
              for (InputIterator temp=first;temp!=last;++temp){
                  tmp.arr[i] = *temp;
                  i++;
              }
          }
          tmp.arr[i] = *it;
          i++;
      }
      if (pos == end()){
          for (InputIterator temp2=first;temp2!=last;++temp2){
                  tmp.arr[i] = *temp2;
                  i++;
          }
      }
      n += count;
      delete [] arr;
      arr = n ? new value_type[n]() : nullptr; 
      for (int j=0;j<n;j++){
          arr[j] = tmp.arr[j];
      }
      m_first = arr;
      m_last = arr + n;
      return arr + dif;
      
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      n++;
      vector tmp(n);
      for (int i=0;i<n-1;i++){
          tmp.arr[i] = arr[i];
      }
      tmp.arr[n-1] = value;
      delete [] arr;
      arr = n ? new value_type[n]() : nullptr;
      for (int j=0;j<n;j++){
          arr[j] = tmp.arr[j];
      }
      m_first = arr;
      m_last = arr + n;
    }

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:   
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions
    void swap(vector& v){
      size_t const t1 = n;
      n = v.n;
      v.n = t1;
      Type * const t2 = arr;
      arr = v.arr;
      v.arr = t2;
  }
  private:
    size_t n;
    value_type* arr;
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik

int main(){
  stepik::vector<int> vec(2);
  vec.push_back(1);
  vec.push_back(4);
  cout << vec.at(0) << "   " << vec.at(1) << endl;
  vec.erase(vec.begin(),vec.end());
  cout << vec.size() << endl;
  return 0;
}
