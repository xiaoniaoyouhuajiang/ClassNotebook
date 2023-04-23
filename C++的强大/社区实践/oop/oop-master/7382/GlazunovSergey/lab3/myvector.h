#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <assert.h>
#include <iostream>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

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

explicit vector(size_t count = 0)
    {
      new_memory(count);
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        new_memory(last - first);
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
    {
        new_memory(init.size());
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other)
    {
        new_memory(other.size());
        std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other)
    {
        m_first = nullptr;
        m_last = nullptr;
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }

    ~vector()
    {
        delete_memory();
    }
      vector& operator=(vector other)
      {
          delete_memory();
          m_first = nullptr;
          m_last = nullptr;
          std::swap(m_first, other.m_first);
          std::swap(m_last, other.m_last);
          return *this;
      }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete_memory();
        new_memory(last - first);
        std::copy(first, last, m_first);
    }
    // resize methods
    void resize(size_t count)
    {
        auto* data = new Type[count]();
        if (count > m_last - m_first)
                std::copy(m_first, m_last, data);
        else
                std::copy(m_first, m_first + count, data);
        delete_memory();
        m_first = data;
        m_last = m_first + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        auto new_size = m_last - m_first - 1;
        auto new_vector = new Type[new_size]();
        auto erase_el = pos - m_first;
        auto to_deleted_element = pos - m_first;
        std::copy(m_first, m_first + erase_el, new_vector);
        std::copy(m_first + erase_el + 1, m_last, new_vector + erase_el);

        delete_memory();

        m_first = new_vector;
        m_last = new_vector + new_size;

       return m_first + erase_el;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if (first == last)
                return m_first + (last - m_first);
        auto new_size = m_last - m_first - (last - first);
        auto new_vector = new Type[new_size]();
        //auto erase_el = last - first;
        auto p1 = first - m_first, p2 = last - m_first;
        std::copy(m_first, m_first + p1, new_vector);
            auto to_first_after_delete = last - m_first;
            std::copy(m_first + p2, m_last, new_vector + p1);

        delete_memory();
        m_first = new_vector;
        m_last = new_vector + new_size;
       return m_first + p1;

    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      auto new_vector_size = m_last - m_first + 1;
            Type* new_data = new Type[new_vector_size]();

            auto to_enserted_element = (pos - m_first);
            std::copy(m_first, m_first + to_enserted_element, new_data);
            new_data[to_enserted_element] = value;
            std::copy(m_first + to_enserted_element, m_last, new_data + to_enserted_element + 1);

            delete_memory();

            m_first = new_data;
            m_last = new_data + new_vector_size;

            return m_first + to_enserted_element;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      if (first == last)
            {
                return m_first + (pos - m_first);
            }

            auto num_new_elements = last - first;

            auto new_vector_size = num_new_elements + m_last - m_first;
            Type* new_data = new Type[new_vector_size]();

            auto first_new_element = pos - m_first;
            std::copy(m_first, m_first + first_new_element, new_data);
            std::copy(first, last, new_data + first_new_element);
            std::copy(m_first + first_new_element, m_last, new_data + first_new_element + num_new_elements);

            delete_memory();

            m_first = new_data;
            m_last = new_data + new_vector_size;

            return m_first + first_new_element;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      auto new_size = m_last - m_first + 1;
      auto new_vector = new Type[new_size]();
      std::copy(m_first, m_last, new_vector);
      new_vector[new_size - 1] = value;
      delete_memory();
      m_first = new_vector;
      m_last = new_vector + new_size;
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
    void print()
    {
        for(int i=0; i<size(); i++)
            std::cout << m_first[i] << ", ";
        std::cout << std::endl;
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
        void new_memory(size_t memory)
        {
            auto* data = memory ? new Type[memory]() : nullptr;

            m_first = data;
            m_last = data + memory;
        }
      void delete_memory()
      {
          delete[] m_first;
      }
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
#endif // MYVECTOR_H
