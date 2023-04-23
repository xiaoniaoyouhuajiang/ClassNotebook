#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <vector>


namespace stepik {
    template<typename Type>
    class vector {
    public:
        typedef Type *iterator;
        typedef const Type *const_iterator;

        typedef Type value_type;

        typedef value_type &reference;
        typedef const value_type &const_reference;

        typedef std::ptrdiff_t difference_type;

        explicit vector(size_t count = 0) {
            if (count <= 0) {
                m_size = 0;
                pointer = nullptr;
            } else {
                m_size = count;
                pointer = new Type[m_size];
            }
            m_first = pointer;
            m_last = pointer + m_size;
        }

        template<typename InputIterator>
        vector(InputIterator first, InputIterator last) {
            size_t size = last - first;
            if (size <= 0) {
                m_size = 0;
                pointer = nullptr;
            } else {
                m_size = size;
                pointer = new Type[m_size];
            }
            for (auto it = first; it != last; it++)
                pointer[it - first] = *it;
            m_first = pointer;
            m_last = pointer + m_size;
        }

        vector(std::initializer_list<Type> init) {
            m_size = init.size();
            pointer = new Type[m_size];
            int i = 0;
            for (auto const &it : init)
                pointer[i++] = it;
            m_first = pointer;
            m_last = pointer + m_size;
        }

        vector(const vector &other) {
            m_size = other.m_size;
            if (m_size == 0)
                pointer = nullptr;
            else
                pointer = new Type[m_size];
            for (auto i = 0; i < m_size; i++)
                pointer[i] = other.pointer[i];
            m_first = pointer;
            m_last = pointer + m_size;
        }

        vector(vector &&other) noexcept {
            m_size = other.m_size;
            pointer = other.pointer;
            m_first = other.m_first;
            m_last = other.m_last;

            other.pointer = nullptr;
            other.m_first = nullptr;
            other.m_last = nullptr;
        }

        ~vector() {
            delete[] pointer;
        }

        //assignment operators
        vector& operator=(const vector& other)
        {
            delete[] pointer;
            m_size = other.m_size;
            if (m_size == 0)
                pointer = nullptr;
            else
                pointer = new Type[m_size];
            for (auto i = 0; i < m_size; i++)
                pointer[i] = other.pointer[i];
            m_first = pointer;
            m_last = pointer + m_size;

            return *this;
        }

        vector& operator=(vector&& other) noexcept
        {
            delete[] pointer;
            m_size = other.m_size;
            pointer = other.pointer;
            m_first = other.m_first;
            m_last = other.m_last;

            other.pointer = nullptr;
            other.m_first = nullptr;
            other.m_last = nullptr;

            return *this;
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            size_t size = last - first;
            delete[] pointer;
            if (size <= 0) {
                m_size = 0;
                pointer = nullptr;
            } else {
                m_size = size;
                pointer = new Type[m_size];
            }
            for (auto it = first; it != last; it++)
                pointer[it - first] = *it;
            m_first = pointer;
            m_last = pointer + m_size;
        }

        // resize methods
        void resize(size_t count)
        {
            if(count <= m_size) {
                m_size = count;
                if(count != m_size) delete[] (pointer + m_size);
                m_first = pointer;
                m_last = pointer + m_size;
            } else {
                size_t old_size = m_size;
                m_size = count;
                Type* new_pointer;
                if(m_size <= 0)
                    new_pointer = nullptr;
                else
                    new_pointer = new Type[m_size];
                for(auto i = 0; i < m_size; i++) {
                    if(i >= old_size) new_pointer[i] = 0;
                    else new_pointer[i] = pointer[i];
                }
                delete[] pointer;
                pointer = new_pointer;
                m_first = pointer;
                m_last = pointer + m_size;
            }
        }

        //erase methods
        iterator erase(const_iterator pos)
        {
            auto position = pos - m_first;
            for(auto i = position; i < m_size - 1; i++)
                pointer[i] = pointer[i+1];
            resize(m_size - 1);
            return m_first + position;
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            auto position = first - m_first;
            for(auto i = position; i < m_size; i++)
                pointer[i] = pointer[i + last - m_first - position];
            resize(m_size - (last - first));
            return m_first + position;
        }

        //insert methods
        iterator insert(const_iterator pos, const Type& value)
        {
            size_t position = pos - m_first;
            resize(m_size + 1);
            for(auto i = m_size - 1; i > position; i--)
                pointer[i] = pointer[i - 1];
            pointer[position] = value;
            return pointer + position;
        }

        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            size_t position = pos - m_first;
            resize(m_size + (last - first));
            for(auto i = m_size - (last - first); i + 1 > position; i--)
                pointer[i + last - first - 1] = pointer[i - 1];
            for(auto i = position; i < position + (last - first); i++)
                pointer[i] = *(first + i - position);
            return pointer + position;
        }

        //push_back methods
        void push_back(const value_type& value)
        {
            resize(m_size + 1);
            pointer[m_size - 1] = value;
        }

        //at methods
        reference at(size_t pos) {
            return checkIndexAndGet(pos);
        }

        const_reference at(size_t pos) const {
            return checkIndexAndGet(pos);
        }

        //[] operators
        reference operator[](size_t pos) {
            return m_first[pos];
        }

        const_reference operator[](size_t pos) const {
            return m_first[pos];
        }

        //*begin methods
        iterator begin() {
            return m_first;
        }

        const_iterator begin() const {
            return m_first;
        }

        //*end methods
        iterator end() {
            return m_last;
        }

        const_iterator end() const {
            return m_last;
        }

        //size method
        size_t size() const {
            return m_last - m_first;
        }

        //empty method
        bool empty() const {
            return m_first == m_last;
        }

    private:
        reference checkIndexAndGet(size_t pos) const {
            if (pos >= size()) {
                throw std::out_of_range("out of range");
            }

            return m_first[pos];
        }

        //your private functions

    private:
        iterator m_first;
        iterator m_last;
        Type *pointer;
        size_t m_size;
    };
}// namespace stepik