#ifndef VECTOR_H
#define VECTOR_H
#include <assert.h>
#include <iostream>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <map>
#include <set>

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
      explicit vector(size_t count = 0){
            m_first = new Type[count];
            m_last = m_first + count;
      }
      friend vector operator^ (const vector <Type> &v1, const vector <Type> &v2){
          vector <Type> tmp1(0), tmp2(0);
          tmp1 = v1&v2;
          tmp2.insert(tmp2.begin(),v1.begin(),v1.end());
          tmp2.insert(tmp2.end(),v2.begin(),v2.end());
          for (size_t i = 0; i < tmp2.size();i++)
              for (size_t j = 0; j < tmp1.size(); j++) 
                  if(tmp2[i] == tmp1[j]){
                      tmp2.erase(tmp2.begin() + i);
                      break;
                  }          
          return tmp2;
      }

      vector operator^= (vector <Type> &v){
          *this = (*this)^(v);
          return *this;
      }

      friend vector operator| (const vector <Type> &v1, const vector <Type> &v2){
          std::set<Type> m;
          m.insert(v1.begin(),v1.end());
          m.insert(v2.begin(),v2.end());
          vector <Type> tmp(0);
          for (auto it: m) {
              tmp.push_back(it);
          }
          return tmp;
      }

      vector operator|= (vector <Type> &v){
          *this = (*this)|(v);
          return *this;
      }

      friend vector operator& (const vector <Type> &v1, const vector <Type> &v2){
          std::map<Type,Type> m;
          vector <Type> tmp(0);
          for (int i=0; i<v1.size(); i++)
            for (int j=0; j<v2.size(); j++){
                if (v1.m_first[i]==v2.m_first[j])
                    m[v1.m_first[i]]=0;
            }

          for (typename std::map<Type,Type>::iterator it=m.begin(); it!=m.end(); it++){
              Type num = it->first;
              tmp.push_back(num);
          }
          /*
          for (auto it:m){
              Type num = it.first;
              tmp.push_back(num);
          }
          */
          return tmp;
      }

      vector operator&= (vector <Type> &v){
          *this = (*this)&(v);
          return *this;
      }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):vector(last - first){
      std::copy(first,last,m_first);
    }

    vector(std::initializer_list<Type> init):vector(init.begin(),init.end()){}

    vector(const vector& other) : vector(other.begin(), other.end()){}

    vector(vector&& other){
      m_first = other.m_first;
      m_last = other.m_last;
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector(){
      delete []m_first;
    }
    void swap(vector& that, vector& other){
        std::swap(that.m_first, other.m_first);
        std::swap(that.m_last, other.m_last);
    }


    //assignment operators
    vector& operator=(const vector& other){
        if(this != &other){
            delete []m_first;
            m_first = new Type[other.size()];
            m_last = m_first + other.size();
            std::copy(other.m_first,other.m_last,m_first);
            return *this;

        }
    }


    vector& operator=(vector&& other){
        if(this != &other){
            delete []m_first;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;
        }
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last){
      vector tmp(first,last);
      swap(*this,tmp);
    }

    // resize methods
    void resize(size_t count){
        iterator end = (count > size()) ? m_last : m_first + count;
        vector temp(count);
        std::move(m_first, end, temp.m_first);
        swap(*this,temp);
    }

    //erase methods
    iterator erase(const_iterator pos){
        size_t tmp = pos - m_first;
        std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
        resize(size() - 1);
        return m_first + tmp;
    }

    iterator erase(const_iterator first, const_iterator last){
        iterator it = const_cast<iterator>(first);
        for(size_t i = 0, count = last - first; i < count; ++i){
            it = erase(it);
        }
        return it;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value){
        size_t s_pos = pos - m_first;
        vector tmp(size()+1);
        std::copy(m_first,m_first+s_pos,tmp.m_first);
        *(tmp.m_first + s_pos) = value;
        std::copy(m_first+s_pos,m_last,tmp.m_first + s_pos+1);
        swap(*this,tmp);
        return m_first + s_pos;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last){
        size_t s_pos = pos - m_first;
        vector tmp(size()+(last-first));
        std::copy(m_first,m_first+s_pos,tmp.m_first);
        std::copy(first,last,tmp.m_first + s_pos);
        std::copy(m_first + s_pos, m_last, tmp.begin() + s_pos + (last - first));
        swap(*this,tmp);
        return m_first + s_pos;
    }

    //push_back methods
    void push_back(const value_type& value){
      insert(this->end(), value);
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

  private:
    iterator m_first;
    iterator m_last;
  };

}// namespace stepik

#endif // VECTOR_H
