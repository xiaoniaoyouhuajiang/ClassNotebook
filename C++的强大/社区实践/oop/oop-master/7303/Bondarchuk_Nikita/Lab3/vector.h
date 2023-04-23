#ifndef VECTOR_H
#define VECTOR_H
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
using namespace std;
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

    explicit vector(size_t count = 0)
    {
        m_first = new Type[count];
        m_last = m_first + count;
      // implement this
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last): vector(last-first)
    {
      copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
    {
      // implement this
    }

    vector(const vector& other)
    {
        m_first = new Type[other.size()];
        m_last = &(m_first[other.size()]);
        copy(other.m_first, other.m_last, m_first);
      // implement this
    }

    vector(vector&& other)
    {
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
      // implement this
    }

    ~vector()
    {
        delete [] m_first;
      // implement this
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
    //assignment operators
        vector& operator=(const vector& other)
        {  if(this != &other)
        {
           vector a(other);
           swap(this->m_first, a.m_first);
           swap(this->m_last, a.m_last);
        }
            return *this;
          // implement this
        }

        vector& operator=(vector&& other)
        {    if(this != &other)
        {
            swap(this->m_first, other.m_first);
           swap(this->m_last, other.m_last);
        }
            return *this;

          // implement this
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
           vector a(first, last);
           swap(this->m_first, a.m_first);
           swap(this->m_last, a.m_last);
          // implement this
        }
        void resize(size_t count)
            {
                vector a(count);
                if(count < (m_last-m_first))
                {
                    copy(m_first, m_first + count, a.m_first);
                    swap(this->m_first, a.m_first);
                    swap(this->m_last, a.m_last);
                }
                else
                {
                    copy(m_first, m_first + (m_last-m_first), a.m_first);
                    swap(this->m_first, a.m_first);
                    swap(this->m_last, a.m_last);
                }
              // implement this
            }

            //erase methods
            iterator erase(const_iterator pos)
            {
                    iterator a = m_first;
                    difference_type size = m_last - m_first;
                    size_t i = 0;

                    while (a != pos) {
                        a++;
                        i++;
                    }
                    rotate(a, a + 1, m_last);

                    resize(size - 1);
                    return  m_first + i;
              // implement this
            }

            iterator erase(const_iterator first, const_iterator last)
            {
                    difference_type  size = last - first;
                    iterator a = m_first;

                    if (size == 0)
                        return a;

                   while(a!= first)
                       a++;
                    for (size_t i = 0; i < size; i++) {
                        a = erase(a);
                    }
                    return a;
              // implement this
            }
            iterator insert(const_iterator pos, const Type& value)
               {
                  difference_type size = pos - m_first;
                  resize(this->size()+1);
                  *(m_last-1) = value;
                  rotate(m_first+size, m_last-1, m_last);
                  return m_first + size;

                 // implement this
               }


               template <typename InputIterator>
               iterator insert(const_iterator pos, InputIterator first, InputIterator last)
               {
                   difference_type size = pos - m_first;
                   resize(this->size() + (last-first));
                   copy(first, last, m_last - (last-first));
                   rotate(m_first+size, m_last - (last-first) , m_last);
                       return m_first + size;
                 // implement this
               }

               //push_back methods
               void push_back(const value_type& value)
               {
                    resize(size()+1);
                   *(m_last-1) = value;
                 // implement this
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
}
#endif // VECTOR_H
