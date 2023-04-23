#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <cstring>

namespace custom
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

    explicit vector(size_t count1 = 0)
    {
            m_first = new Type[ count1 ];
            m_last = m_first + count1;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        unsigned int count2 = last - first;
        m_first = new Type[ count2 ];
        for( unsigned int i = 0; i < count2; first++, i++ )
        {
            m_first[i] = *first;
        }
        m_last = m_first + count2;
    }

    vector(std::initializer_list<Type> init)
    {
        m_first = new Type[ init.size() ];
        unsigned int i = 0;
        for( auto item : init )
                m_first[i++] = item;
        m_last = m_first + init.size();
    }

    vector(const vector& other)
    {
        unsigned int count3;
        count3 = other.size();
        m_first = new Type[ count3 ];
        for( unsigned int i = 0; i < count3; i++ )
        {
            m_first[i] = other[i];
        }
        m_last = m_first + count3;
    }

    void swap(vector& first, vector& second)
     {
         using std::swap;
         swap(first.m_first, second.m_first);
         swap(first.m_last, second.m_last);
     }

    vector(vector&& other) : vector()
    {
        swap(*this, other);
    }

    ~vector()
    {
        delete [] m_first;
    }

    template<typename T> //Debug print
    void print(T* buf, int size)
    {
        for( int i = 0; i < size; i++)
            std::cout << i << ' ' << *(buf + i) << '\n';
        std::cout << "size: " << size << '\n' << '\n';
    }

    iterator insert(const_iterator pos, const Type& value)
    {
        unsigned int count = size() + 1;
        Type* buff = new Type[ count ];
        iterator p = &m_first[ pos - m_first ];
        iterator b = std::copy( m_first, p, buff );
        std::copy( p, m_last, b + 1 );
        *(b) = value;
        delete[] m_first;
        m_first = new Type[ count ];
        std::copy( buff, buff + count, m_first );
        delete[] buff;
        m_last = m_first + count;

        return &m_first[ pos - m_first ];
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
         vector buff(size()+(last-first));
         size_t n = (pos-begin());
         std::copy(const_iterator(begin()), pos, buff.begin());
         std::copy(first, last, buff.begin()+n);

         if (pos+1 < end())
             std::copy(pos,
                       const_iterator(end()),
                       buff.begin()+n+(last-first));

           buff.swap(buff, *this );
           return begin()+n;
     }

    void push_back(const value_type& value)
    {
        vector<Type> buff;
        buff = *this;
        delete [] m_first;
        m_first = new Type[ buff.size() + 1 ];
        m_last = m_first + buff.size() + 1;
        std::copy( buff.begin(), buff.end(), m_first );
        m_first[ buff.size() ] = value;
    }

    void resize(size_t count)
    {
        vector buff( *this );
        delete[] m_first;
        m_first = new Type[ count ];
        m_last = m_first + count;
        count = count > buff.size() ? buff.size() : count;
        for( unsigned int i = 0; i < count; i++ )
        {
            m_first[ i ] = buff.m_first[ i ];
        }
    }

    iterator erase(const_iterator pos)
    {
        iterator iit = &m_first[pos - m_first];
        unsigned int num = m_last - iit - 1;
        memmove(iit, iit + 1, (num * sizeof(Type)));
        --m_last;
        return iit;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        iterator f = &m_first[first - m_first];
        if (first == last) return f;
        iterator ff = &m_first[ last - m_first ];
        std::memmove( f, last, ((m_last - ff) * sizeof(Type)) );
        m_last -= last - first;
        return f;
    }

    vector& operator=(const vector& other)
    {
            unsigned int count4 = other.m_last - other.m_first;
            delete [] m_first;
            m_first = new Type[ count4 ];

            for( unsigned int i = 0; i < count4; i++ )
           {
               m_first[i] = other.m_first[i];
           }

            m_last = m_first + count4;
            return *this;
    }

    vector& operator=(vector&& other)
    {
        swap(*this, other);
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
          int count5 = last - first;
          delete [] m_first;
          m_first = new Type[ count5 ];
          for( unsigned int i = 0; i < count5; ++i, ++first )
          {
              m_first[i] = *first;
          }
          m_last = m_first + count5;
    }

    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    size_t size() const
    {
      return m_last - m_first;
    }

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

  private:
    iterator m_first;
    iterator m_last;
  };
}


template <typename T> //Дебаг функция для проверки move
custom::vector<T> meh( std::initializer_list<T> init )
{
    custom::vector<T> che(init);
    return che;
}
