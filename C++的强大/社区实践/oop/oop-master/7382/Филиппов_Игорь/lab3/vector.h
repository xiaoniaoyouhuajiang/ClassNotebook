#include <assert.h>
#include <algorithm> 
#include <cstddef> 
#include <initializer_list>
#include <stdexcept>
#include <iostream>

#include <vector>
#include <bits/streambuf_iterator.h>

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

        explicit vector(size_t new_size = 0)
        {
            allocate(new_size);
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            allocate(last - first);

            std::copy(first, last, m_first);
        }

        vector(std::initializer_list<Type> init)
        {
            allocate(init.size());

            std::copy(init.begin(), init.end(), m_first);
        }

        vector(const vector& other)
        {
            allocate(other.size());

            std::copy(other.begin(), other.end(), m_first);
        }

        vector(vector&& other) noexcept
        {
            m_first = m_last = nullptr;

            std::swap(m_first, other.m_first);
            std::swap(m_last, other.m_last);
        }

        ~vector()
        {
            delete_data();
        }

        
        vector& operator=(vector other)
        {
            delete_data();
            m_first = m_last = nullptr;

            std::swap(m_first, other.m_first);
            std::swap(m_last, other.m_last);

            return *this;
        }

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            delete_data();

            allocate(last - first);

            std::copy(first, last, m_first);
        }

        void resize(size_t new_size)
        {
            Type* new_data = new Type[new_size]();

            if (new_size > m_last - m_first)
            {
                std::copy(m_first, m_last, new_data);
            }
            else
            {
                std::copy(m_first, m_first + new_size, new_data);
            }

            delete_data();

            m_first = new_data;
            m_last = new_data + new_size;
        }

        iterator erase(const_iterator pos)
        {
            auto new_vector_size = m_last - m_first - 1;
            Type* new_data = new Type[new_vector_size]();

            auto to_deleted_element = pos - m_first;
            std::copy(m_first, m_first + to_deleted_element, new_data);
            std::copy(m_first + to_deleted_element + 1, m_last, new_data + to_deleted_element);

            delete_data();

            m_first = new_data;
            m_last = new_data + new_vector_size;

            return m_first + to_deleted_element;
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            if (first == last)
                return m_first + (last - m_first);

            auto new_vector_size = m_last - m_first - (last - first);
            Type* new_data = new Type[new_vector_size]();

            auto num_before_deletion = first - m_first;
            std::copy(m_first, m_first + num_before_deletion, new_data);
            auto to_first_after_delete = last - m_first;
            std::copy(m_first + to_first_after_delete, m_last, new_data + num_before_deletion);

            delete_data();

            m_first = new_data;
            m_last = new_data + new_vector_size;

            return m_first + num_before_deletion;
        }

        iterator insert(const_iterator pos, const Type& value)
        {
            auto new_vector_size = m_last - m_first + 1;
            Type* new_data = new Type[new_vector_size]();

            auto to_enserted_element = (pos - m_first);
            std::copy(m_first, m_first + to_enserted_element, new_data);
            new_data[to_enserted_element] = value;
            std::copy(m_first + to_enserted_element, m_last, new_data + to_enserted_element + 1);

            delete_data();

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

            delete_data();

            m_first = new_data;
            m_last = new_data + new_vector_size;

            return m_first + first_new_element;
        }

        void push_back(const value_type& value)
        {
            auto new_vector_size = m_last - m_first + 1;
            Type* new_data = new Type[new_vector_size]();

            std::copy(m_first, m_last, new_data);

            new_data[new_vector_size - 1] = value;

            delete_data();

            m_first = new_data;
            m_last = new_data + new_vector_size;
        }

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

        void allocate(size_t memory_size)
        {
            Type* data = memory_size ? new Type[memory_size]() : nullptr;

            m_first = data;
            m_last = data + memory_size;
        }

        void delete_data()
        {
            delete[] m_first;
        }

    private:
        iterator m_first;
        iterator m_last;
    };
}// namespace